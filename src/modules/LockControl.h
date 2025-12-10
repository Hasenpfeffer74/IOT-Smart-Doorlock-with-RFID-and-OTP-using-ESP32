// ═══════════════════════════════════════════════════════════
// CẬP NHẬT FILE: LockControl.h
// ═══════════════════════════════════════════════════════════

#ifndef LOCKCONTROL_H
#define LOCKCONTROL_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

class LockControl {
  private:
    bool locked;
    void beepSuccess();
    void beepError();
    void ledOn();
    void ledOff();
    void ledBlink(int times, int delayMs = 200);
    void ledBlinkWithBuzzer(int times, int delayMs = 200);
    
  public:
    LockControl();
    void init();
    void unlock(String method, LiquidCrystal_I2C* lcd, void (*sendTelegramFunc)(String) = nullptr);
    void lock();
    bool isLocked();
    void showAccessDenied(LiquidCrystal_I2C* lcd, String reason);
};

#endif