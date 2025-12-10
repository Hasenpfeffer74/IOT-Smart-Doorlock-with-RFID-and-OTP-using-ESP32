// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/LED/LED_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <Arduino.h>

/**
 * @brief Status LED Driver
 * @details Controls status LED for visual feedback
 * 
 * Patterns:
 * - Solid ON: System active
 * - Blinking: Processing
 * - OFF: Idle/Error
 */
class LED_Driver {
private:
    uint8_t pin;
    bool state;

public:
    /**
     * @brief Constructor
     * @param led_pin GPIO pin (default: 14)
     */
    LED_Driver(uint8_t led_pin = 14);
    
    /**
     * @brief Initialize LED
     * @note Must call BSP_GPIO::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Turn LED on
     */
    void on();
    
    /**
     * @brief Turn LED off
     */
    void off();
    
    /**
     * @brief Toggle LED state
     */
    void toggle();
    
    /**
     * @brief Get current LED state
     * @return true if on, false if off
     */
    bool isOn() const;
    
    /**
     * @brief Blink LED
     * @param times Number of blinks
     * @param delay_ms Delay between blinks (default: 200ms)
     */
    void blink(uint8_t times, uint16_t delay_ms = 200);
    
    /**
     * @brief Blink LED continuously (blocking)
     * @param duration_ms Total duration
     * @param delay_ms Delay between blinks
     */
    void blinkContinuous(uint16_t duration_ms, uint16_t delay_ms = 200);
};

#endif // LED_DRIVER_H