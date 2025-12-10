// ═══════════════════════════════════════════════════════════
// FILE: PasswordModule.h
// ═══════════════════════════════════════════════════════════

#ifndef PASSWORDMODULE_H
#define PASSWORDMODULE_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

class PasswordModule {
  private:
    String inputBuffer;
    void displayMask(LiquidCrystal_I2C* lcd);
    
  public:
    PasswordModule();
    void init();
    void showInputScreen(LiquidCrystal_I2C* lcd);
    int handleInput(char key, LiquidCrystal_I2C* lcd);
    void reset();
};

#endif