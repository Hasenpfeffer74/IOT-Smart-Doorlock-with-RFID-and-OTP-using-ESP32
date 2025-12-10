// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_SPI.cpp
// ═══════════════════════════════════════════════════════════
#include "BSP_SPI.h"

// Pin definitions from Config
#define RFID_SCK_PIN  19
#define RFID_MISO_PIN 5
#define RFID_MOSI_PIN 23
#define RFID_SS_PIN   18

bool BSP_SPI::initialized = false;

void BSP_SPI::init() {
    if (initialized) {
        Serial.println("⚠️  BSP_SPI: Already initialized");
        return;
    }
    
    Serial.println("🔧 BSP_SPI: Initializing SPI bus...");
    Serial.printf("   - SCK:  GPIO %d\n", RFID_SCK_PIN);
    Serial.printf("   - MISO: GPIO %d\n", RFID_MISO_PIN);
    Serial.printf("   - MOSI: GPIO %d\n", RFID_MOSI_PIN);
    
    // Initialize SPI with custom pins
    SPI.begin(RFID_SCK_PIN, RFID_MISO_PIN, RFID_MOSI_PIN, RFID_SS_PIN);
    
    initialized = true;
    Serial.println("✅ BSP_SPI: Initialization complete");
}

SPIClass* BSP_SPI::getInstance() {
    if (!initialized) {
        Serial.println("❌ BSP_SPI: Not initialized! Call init() first.");
        return nullptr;
    }
    return &SPI;
}

bool BSP_SPI::isInitialized() {
    return initialized;
}