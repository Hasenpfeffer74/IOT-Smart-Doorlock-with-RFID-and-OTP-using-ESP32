// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/RFID/RFID_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef RFID_DRIVER_H
#define RFID_DRIVER_H

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

/**
 * @brief RFID Reader Driver (MFRC522)
 * @details Manages RFID card reading and validation
 * 
 * Hardware: MFRC522 module (13.56MHz)
 * Connection: SPI bus (managed by BSP_SPI)
 */
class RFID_Driver {
private:
    MFRC522 rfid;
    String lastCardUID;
    unsigned long lastReadTime;
    
    static const uint16_t DEBOUNCE_TIME = 1000; // 1 second debounce

public:
    /**
     * @brief Constructor
     * @param ss_pin Slave Select pin (default: 18)
     * @param rst_pin Reset pin (default: 13)
     */
    RFID_Driver(uint8_t ss_pin = 18, uint8_t rst_pin = 13);
    
    /**
     * @brief Initialize RFID module
     * @note Must call BSP_SPI::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Read card UID if present
     * @return Card UID string (uppercase hex), empty if no card
     */
    String readCard();
    
    /**
     * @brief Check if card UID is valid (registered)
     * @param uid Card UID to check
     * @return true if valid, false otherwise
     */
    bool isCardValid(const String& uid);
    
    /**
     * @brief Get number of registered cards
     * @return Count of valid cards
     */
    uint8_t getValidCardCount();
    
    /**
     * @brief Get firmware version of RFID reader
     * @return Version as byte
     */
    uint8_t getFirmwareVersion();
};

#endif // RFID_DRIVER_H