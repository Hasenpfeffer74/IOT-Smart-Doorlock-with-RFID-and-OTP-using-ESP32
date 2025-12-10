// ═══════════════════════════════════════════════════════════
// FILE: RFIDModule.h
// ═══════════════════════════════════════════════════════════

#ifndef RFIDMODULE_H
#define RFIDMODULE_H

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include "Config.h"

class RFIDModule {
  private:
    MFRC522 rfid;
    
  public:
    RFIDModule();
    void init();
    String checkCard();
    bool isValidCard(String uid);
    int getValidCardCount();
};

#endif