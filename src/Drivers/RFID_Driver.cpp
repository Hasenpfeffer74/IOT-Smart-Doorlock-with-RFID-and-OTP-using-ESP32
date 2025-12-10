// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/RFID/RFID_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "RFID_Driver.h"

// Valid card UIDs (should match Config.h)
const String VALID_RFID_UIDS[] = {
    "FA904A06"
};
const uint8_t VALID_RFID_COUNT = sizeof(VALID_RFID_UIDS) / sizeof(VALID_RFID_UIDS[0]);

RFID_Driver::RFID_Driver(uint8_t ss_pin, uint8_t rst_pin) 
    : rfid(ss_pin, rst_pin), lastReadTime(0) {
}

void RFID_Driver::init() {
    Serial.println("🔧 RFID_Driver: Initializing...");
    
    // Initialize RFID module (SPI already initialized by BSP)
    rfid.PCD_Init();
    
    // Get firmware version
    uint8_t version = rfid.PCD_ReadRegister(rfid.VersionReg);
    Serial.printf("   - Firmware: v%d.0\n", version);
    Serial.printf("   - Valid cards: %d\n", VALID_RFID_COUNT);
    
    if (version == 0x00 || version == 0xFF) {
        Serial.println("   ⚠️  WARNING: RFID reader not detected!");
    } else {
        Serial.println("✅ RFID_Driver: Ready");
    }
}

String RFID_Driver::readCard() {
    // Check for new card
    if (!rfid.PICC_IsNewCardPresent()) {
        return "";
    }
    
    // Read card serial
    if (!rfid.PICC_ReadCardSerial()) {
        return "";
    }
    
    // Build UID string
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) {
            uid += "0";
        }
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    uid.toUpperCase();
    
    // Debounce: ignore same card read within 1 second
    unsigned long now = millis();
    if (uid == lastCardUID && (now - lastReadTime) < DEBOUNCE_TIME) {
        rfid.PICC_HaltA();
        return "";
    }
    
    lastCardUID = uid;
    lastReadTime = now;
    
    Serial.printf("📇 RFID: Card detected [%s]\n", uid.c_str());
    
    // Halt card to stop reading
    rfid.PICC_HaltA();
    
    return uid;
}

bool RFID_Driver::isCardValid(const String& uid) {
    String uid_upper = uid;
    uid_upper.toUpperCase();
    
    for (uint8_t i = 0; i < VALID_RFID_COUNT; i++) {
        if (uid_upper == VALID_RFID_UIDS[i]) {
            return true;
        }
    }
    return false;
}

uint8_t RFID_Driver::getValidCardCount() {
    return VALID_RFID_COUNT;
}

uint8_t RFID_Driver::getFirmwareVersion() {
    return rfid.PCD_ReadRegister(rfid.VersionReg);
}