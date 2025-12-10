  // ═══════════════════════════════════════════════════════════
// FILE: src/App/PasswordManager/PasswordManager.h
// ═══════════════════════════════════════════════════════════
#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <Arduino.h>
#include "Drivers/LCD/LCD_Driver.h"

/**
 * @brief PIN Password Manager
 * @details Manages PIN input and validation
 */
class PasswordManager {
private:
    String correctPassword;
    String inputBuffer;
    LCD_Driver* lcd;
    uint8_t maxLength;

public:
    /**
     * @brief Constructor
     * @param password Correct password (default: "1234")
     * @param lcd_driver Pointer to LCD_Driver
     * @param max_len Maximum password length (default: 4)
     */
    PasswordManager(const String& password, LCD_Driver* lcd_driver, uint8_t max_len = 4);
    
    /**
     * @brief Initialize password manager
     */
    void init();
    
    /**
     * @brief Add digit to input buffer
     * @param digit Digit character (0-9)
     * @return true if buffer is full
     */
    bool addDigit(char digit);
    
    /**
     * @brief Verify entered password
     * @return true if correct, false otherwise
     */
    bool verify();
    
    /**
     * @brief Get input buffer
     * @return Current input buffer
     */
    String getInputBuffer() const;
    
    /**
     * @brief Get input buffer length
     * @return Buffer length
     */
    uint8_t getInputLength() const;
    
    /**
     * @brief Clear input buffer
     */
    void clearInput();
    
    /**
     * @brief Reset password manager
     */
    void reset();
    
    /**
     * @brief Show input screen on LCD
     */
    void showInputScreen();
    
    /**
     * @brief Update input display on LCD
     */
    void updateInputDisplay();
    
    /**
     * @brief Change password
     * @param new_password New password
     */
    void changePassword(const String& new_password);
};

#endif // PASSWORD_MANAGER_H