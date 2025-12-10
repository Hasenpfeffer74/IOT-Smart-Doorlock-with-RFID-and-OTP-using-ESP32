// ═══════════════════════════════════════════════════════════
// FILE: src/App/DoorlockController/DoorlockController.h
// ═══════════════════════════════════════════════════════════
#ifndef DOORLOCK_CONTROLLER_H
#define DOORLOCK_CONTROLLER_H

#include <Arduino.h>
#include "Drivers/Lock/Lock_Driver.h"
#include "Drivers/LED/LED_Driver.h"
#include "Drivers/Buzzer/Buzzer_Driver.h"
#include "Drivers/LCD/LCD_Driver.h"
#include "App/TelegramNotifier/TelegramNotifier.h"

/**
 * @brief Doorlock Main Controller
 * @details Orchestrates lock, LED, buzzer, LCD, and notifications
 */
class DoorlockController {
private:
    Lock_Driver* lock;
    LED_Driver* led;
    Buzzer_Driver* buzzer;
    LCD_Driver* lcd;
    TelegramNotifier* telegram;
    
    static const uint16_t UNLOCK_DURATION = 5000; // 5 seconds

public:
    /**
     * @brief Constructor
     * @param lock_driver Pointer to Lock_Driver
     * @param led_driver Pointer to LED_Driver
     * @param buzzer_driver Pointer to Buzzer_Driver
     * @param lcd_driver Pointer to LCD_Driver
     * @param telegram_notifier Pointer to TelegramNotifier
     */
    DoorlockController(Lock_Driver* lock_driver, LED_Driver* led_driver,
                       Buzzer_Driver* buzzer_driver, LCD_Driver* lcd_driver,
                       TelegramNotifier* telegram_notifier);
    
    /**
     * @brief Initialize doorlock controller
     */
    void init();
    
    /**
     * @brief Unlock door sequence
     * @param method Unlock method (RFID/OTP/PASSWORD)
     */
    void unlockDoor(const String& method);
    
    /**
     * @brief Lock door
     */
    void lockDoor();
    
    /**
     * @brief Show access denied screen
     * @param reason Denial reason
     */
    void showAccessDenied(const String& reason);
    
    /**
     * @brief Show countdown on LCD
     * @param seconds Countdown duration in seconds
     */
    void showCountdown(uint8_t seconds);
    
    /**
     * @brief Check if door is locked
     * @return true if locked, false otherwise
     */
    bool isLocked() const;
};

#endif // DOORLOCK_CONTROLLER_H