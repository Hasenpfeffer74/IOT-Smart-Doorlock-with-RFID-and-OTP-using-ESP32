// ═══════════════════════════════════════════════════════════
// FILE: src/App/DoorlockController/DoorlockController.h
// ═══════════════════════════════════════════════════════════
#ifndef DOORLOCKCONTROLLER_H
#define DOORLOCKCONTROLLER_H

#include <Arduino.h>
#include "../../Drivers/Lock/Lock_Driver.h"
#include "../../Drivers/LED/LED_Driver.h"
#include "../../Drivers/Buzzer/Buzzer_Driver.h"
#include "../../Drivers/LCD/LCD_Driver.h"
#include "../TelegramNotifier/TelegramNotifier.h"
#include "../../Config.h"

class DoorlockController {
public:
    DoorlockController(Lock_Driver* lock_driver, LED_Driver* led_driver, 
                      Buzzer_Driver* buzzer_driver, LCD_Driver* lcd_driver,
                      TelegramNotifier* telegram_notifier);
    
    void init();
    void unlockDoor(const String& method);      // Changed from unlock
    void lockDoor();                            // Added
    void showAccessDenied(const String& reason); // Added
    void showCountdown(uint8_t seconds);        // Added
    bool isLocked() const;                      // Changed from isUnlocked

private:
    Lock_Driver* lock;
    LED_Driver* led;
    Buzzer_Driver* buzzer;
    LCD_Driver* lcd;
    TelegramNotifier* telegram;
};

#endif // DOORLOCKCONTROLLER_H
