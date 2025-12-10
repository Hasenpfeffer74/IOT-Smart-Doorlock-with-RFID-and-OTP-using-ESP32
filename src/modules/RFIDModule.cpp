// ═══════════════════════════════════════════════════════════
// FILE: RFIDModule.cpp
// ═══════════════════════════════════════════════════════════

#include "RFIDModule.h"

RFIDModule::RFIDModule() : rfid(RFID_SS_PIN, RFID_RST_PIN) {}

void RFIDModule::init() {
  SPI.begin(RFID_SCK_PIN, RFID_MISO_PIN, RFID_MOSI_PIN, RFID_SS_PIN);
  rfid.PCD_Init();
  Serial.println("RFID Module Ready");
}

String RFIDModule::checkCard() {
  if (!rfid.PICC_IsNewCardPresent()) return "";
  if (!rfid.PICC_ReadCardSerial()) return "";

  String uid_str = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) uid_str += "0";
    uid_str += String(rfid.uid.uidByte[i], HEX);
  }
  uid_str.toUpperCase();

  Serial.print("RFID Detected: ");
  Serial.println(uid_str);

  rfid.PICC_HaltA();
  
  return uid_str;
}

bool RFIDModule::isValidCard(String uid) {
  uid.toUpperCase();
  for (int i = 0; i < VALID_RFID_COUNT; i++) {
    if (uid == VALID_RFID_UIDS[i]) return true;
  }
  return false;
}

int RFIDModule::getValidCardCount() {
  return VALID_RFID_COUNT;
}