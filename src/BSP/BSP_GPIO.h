// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_GPIO.h
// ═══════════════════════════════════════════════════════════
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <Arduino.h>

/**
 * @brief Board Support Package for GPIO Configuration
 * @details Centralizes all GPIO pin initialization
 * 
 * Pin Allocation:
 * ┌─────────────────────────────────────────────┐
 * │ OUTPUT PINS                                 │
 * ├─────────────────────────────────────────────┤
 * │ Lock Control:  GPIO 2  (Relay to Solenoid) │
 * │ LED Indicator: GPIO 14 (Status LED)        │
 * │ Buzzer:        GPIO 27 (5V Buzzer)         │
 * └─────────────────────────────────────────────┘
 * 
 * ┌─────────────────────────────────────────────┐
 * │ INPUT PINS (Keypad 4x4)                     │
 * ├─────────────────────────────────────────────┤
 * │ Rows:    GPIO 33, 32, 4, 15                │
 * │ Columns: GPIO 26, 25, 17, 16               │
 * └─────────────────────────────────────────────┘
 */
class BSP_GPIO {
public:
    /**
     * @brief Initialize all GPIO pins
     * @note Call this ONCE in setup() before any driver init
     */
    static void init();
    
    /**
     * @brief Check if GPIO is initialized
     * @return true if initialized, false otherwise
     */
    static bool isInitialized();
    
    /**
     * @brief Print GPIO configuration summary
     */
    static void printConfig();

private:
    static bool initialized;
    
    /**
     * @brief Initialize output pins (Lock, LED, Buzzer)
     */
    static void initOutputPins();
    
    /**
     * @brief Initialize input pins (Keypad rows/cols)
     */
    static void initInputPins();
};

#endif // BSP_GPIO_H