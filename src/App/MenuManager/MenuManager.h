// ═══════════════════════════════════════════════════════════
// FILE: src/App/MenuManager/MenuManager.h
// ═══════════════════════════════════════════════════════════
#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <Arduino.h>
#include "Drivers/LCD/LCD_Driver.h"
#include "Drivers/RFID/RFID_Driver.h"

/**
 * @brief Menu Display Manager
 * @details Manages all LCD menu screens
 */
class MenuManager {
private:
    LCD_Driver* lcd;
    RFID_Driver* rfid;

public:
    /**
     * @brief Constructor
     * @param lcd_driver Pointer to LCD_Driver
     * @param rfid_driver Pointer to RFID_Driver
     */
    MenuManager(LCD_Driver* lcd_driver, RFID_Driver* rfid_driver);
    
    /**
     * @brief Initialize menu manager
     */
    void init();
    
    /**
     * @brief Show main menu
     * Options: A=OTP, B=Pass, C=RFID, D=Info
     */
    void showMainMenu();
    
    /**
     * @brief Show RFID card info
     */
    void showRFIDInfo();
    
    /**
     * @brief Show system information
     * @param wifi_connected WiFi connection status
     * @param door_locked Door lock status
     */
    void showSystemInfo(bool wifi_connected, bool door_locked);
    
    /**
     * @brief Show welcome message at startup
     */
    void showWelcome();
    
    /**
     * @brief Show "scanning card" prompt
     */
    void showScanCardPrompt();
};

#endif // MENU_MANAGER_H