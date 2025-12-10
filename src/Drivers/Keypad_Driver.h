// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Keypad/Keypad_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef KEYPAD_DRIVER_H
#define KEYPAD_DRIVER_H

#include <Arduino.h>
#include <Keypad.h>

/**
 * @brief 4x4 Matrix Keypad Driver
 * @details Scans keypad matrix and returns pressed keys
 * 
 * Layout:
 *   1 2 3 A
 *   4 5 6 B
 *   7 8 9 C
 *   * 0 # D
 */
class Keypad_Driver {
private:
    Keypad* keypad;
    char lastKey;
    unsigned long lastPressTime;
    
    static const uint16_t DEBOUNCE_TIME = 200; // 200ms debounce

public:
    /**
     * @brief Constructor
     * @note GPIO pins are configured by BSP_GPIO
     */
    Keypad_Driver();
    
    /**
     * @brief Destructor
     */
    ~Keypad_Driver();
    
    /**
     * @brief Initialize keypad
     * @note Must call BSP_GPIO::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Get pressed key (non-blocking)
     * @return Pressed key character, or '\0' if no key pressed
     */
    char getKey();
    
    /**
     * @brief Check if any key is currently pressed
     * @return true if key is pressed, false otherwise
     */
    bool isPressed();
    
    /**
     * @brief Wait for key press (blocking)
     * @param timeout_ms Timeout in milliseconds (0 = no timeout)
     * @return Pressed key, or '\0' if timeout
     */
    char waitForKey(uint16_t timeout_ms = 0);
};

#endif // KEYPAD_DRIVER_H