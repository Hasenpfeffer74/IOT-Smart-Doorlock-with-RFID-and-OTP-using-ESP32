// ═══════════════════════════════════════════════════════════
// FILE: OTPModule.h
// ═══════════════════════════════════════════════════════════

#ifndef OTPMODULE_H
#define OTPMODULE_H

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

class OTPModule {
  private:
    int generatedOTP;
    unsigned long otpTime;
    String inputBuffer;
    
    void connectWiFi();
    
  public:
    OTPModule();
    void init();
    void generateOTP(LiquidCrystal_I2C* lcd);
    void showInputScreen(LiquidCrystal_I2C* lcd);
    int handleInput(char key, LiquidCrystal_I2C* lcd);
    void sendTelegramMessage(String msg);
    void reset();
};

#endif