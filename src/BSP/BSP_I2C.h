// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_I2C.h
// ═══════════════════════════════════════════════════════════
#ifndef BSP_I2C_H
#define BSP_I2C_H

#include <Arduino.h>
#include <Wire.h>

/**
 * @brief Board Support Package for I2C Bus
 * @details Manages I2C initialization for LCD 1602 module
 * 
 * Pin Configuration:
 * - SDA: GPIO 21 (default ESP32)
 * - SCL: GPIO 22 (default ESP32)
 * 
 * LCD Address: 0x27 (default for most I2C LCD modules)
 */
class BSP_I2C {
public:
    /**
     * @brief Initialize I2C bus
     * @note Call this ONCE in setup() before any I2C device init
     * @param sda_pin SDA pin number (default: 21)
     * @param scl_pin SCL pin number (default: 22)
     * @param frequency I2C clock frequency in Hz (default: 100kHz)
     */
    static void init(int sda_pin = 21, int scl_pin = 22, uint32_t frequency = 100000);
    
    /**
     * @brief Get I2C instance pointer
     * @return Pointer to Wire object
     */
    static TwoWire* getInstance();
    
    /**
     * @brief Check if I2C is initialized
     * @return true if initialized, false otherwise
     */
    static bool isInitialized();
    
    /**
     * @brief Scan I2C bus for connected devices
     * @note Useful for debugging - prints all found I2C addresses
     */
    static void scanDevices();

private:
    static bool initialized;
    static int sda;
    static int scl;
};

#endif // BSP_I2C_H