// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_SPI.h
// ═══════════════════════════════════════════════════════════
#ifndef BSP_SPI_H
#define BSP_SPI_H

#include <Arduino.h>
#include <SPI.h>

/**
 * @brief Board Support Package for SPI Bus
 * @details Manages SPI initialization for RFID-RC522 module
 * 
 * Pin Configuration:
 * - SCK:  GPIO 19
 * - MISO: GPIO 5
 * - MOSI: GPIO 23
 * - SS:   GPIO 18 (handled by RFID driver)
 */
class BSP_SPI {
public:
    /**
     * @brief Initialize SPI bus with custom pins
     * @note Call this ONCE in setup() before any SPI device init
     */
    static void init();
    
    /**
     * @brief Get SPI instance pointer
     * @return Pointer to SPI object
     */
    static SPIClass* getInstance();
    
    /**
     * @brief Check if SPI is initialized
     * @return true if initialized, false otherwise
     */
    static bool isInitialized();

private:
    static bool initialized;
};

#endif // BSP_SPI_H

