// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Buzzer/Buzzer_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef BUZZER_DRIVER_H
#define BUZZER_DRIVER_H

#include <Arduino.h>

/**
 * @brief Active Buzzer Driver
 * @details Controls 5V active buzzer for audio feedback
 * 
 * Sound Patterns:
 * - Success: 1 beep (300ms)
 * - Error: 2 beeps (200ms each)
 * - Warning: 3 beeps (150ms each)
 */
class Buzzer_Driver {
private:
    uint8_t pin;
    bool enabled;

public:
    /**
     * @brief Constructor
     * @param buzzer_pin GPIO pin (default: 27)
     */
    Buzzer_Driver(uint8_t buzzer_pin = 27);
    
    /**
     * @brief Initialize buzzer
     * @note Must call BSP_GPIO::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Enable/disable buzzer
     * @param enable true to enable, false to disable
     */
    void setEnabled(bool enable);
    
    /**
     * @brief Single beep
     * @param duration_ms Beep duration in milliseconds
     */
    void beep(uint16_t duration_ms);
    
    /**
     * @brief Success sound (1 beep)
     */
    void beepSuccess();
    
    /**
     * @brief Error sound (2 quick beeps)
     */
    void beepError();
    
    /**
     * @brief Warning sound (3 quick beeps)
     */
    void beepWarning();
    
    /**
     * @brief Custom pattern
     * @param times Number of beeps
     * @param duration_ms Duration of each beep
     * @param pause_ms Pause between beeps
     */
    void beepPattern(uint8_t times, uint16_t duration_ms, uint16_t pause_ms);

private:
    void on();
    void off();
};

#endif // BUZZER_DRIVER_H