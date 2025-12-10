// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/LCD/LCD_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

/**
 * @brief LCD 1602 Display Driver (I2C)
 * @details 16x2 character display with I2C interface
 * 
 * Hardware: LCD1602 with I2C backpack (PCF8574)
 * Address: 0x27 (default, some use 0x3F)
 * Connection: I2C bus (managed by BSP_I2C)
 */
class LCD_Driver {
private:
    LiquidCrystal_I2C lcd;
    uint8_t cols;
    uint8_t rows;

public:
    /**
     * @brief Constructor
     * @param address I2C address (default: 0x27)
     * @param cols Number of columns (default: 16)
     * @param rows Number of rows (default: 2)
     */
    LCD_Driver(uint8_t address = 0x27, uint8_t cols = 16, uint8_t rows = 2);
    
    /**
     * @brief Initialize LCD display
     * @note Must call BSP_I2C::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Clear display
     */
    void clear();
    
    /**
     * @brief Turn backlight on
     */
    void backlightOn();
    
    /**
     * @brief Turn backlight off
     */
    void backlightOff();
    
    /**
     * @brief Set cursor position
     * @param col Column (0-15)
     * @param row Row (0-1)
     */
    void setCursor(uint8_t col, uint8_t row);
    
    /**
     * @brief Print text at current cursor position
     * @param text Text to print
     */
    void print(const String& text);
    
    /**
     * @brief Print text at specific position
     * @param col Column (0-15)
     * @param row Row (0-1)
     * @param text Text to print
     */
    void printAt(uint8_t col, uint8_t row, const String& text);
    
    /**
     * @brief Show two-line message
     * @param line1 First line text (will be centered if < 16 chars)
     * @param line2 Second line text (will be centered if < 16 chars)
     */
    void showMessage(const String& line1, const String& line2 = "");
    
    /**
     * @brief Show message for specific duration
     * @param line1 First line
     * @param line2 Second line
     * @param duration_ms Display duration in milliseconds
     */
    void showMessageTimed(const String& line1, const String& line2, uint16_t duration_ms);
    
    /**
     * @brief Get number of columns
     */
    uint8_t getCols() const { return cols; }
    
    /**
     * @brief Get number of rows
     */
    uint8_t getRows() const { return rows; }
};

#endif // LCD_DRIVER_H