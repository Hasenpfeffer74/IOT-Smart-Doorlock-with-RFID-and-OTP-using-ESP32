// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/LCD/LCD_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "LCD_Driver.h"

LCD_Driver::LCD_Driver(uint8_t address, uint8_t cols, uint8_t rows)
    : lcd(address, cols, rows), cols(cols), rows(rows) {
}

void LCD_Driver::init() {
    Serial.println("🔧 LCD_Driver: Initializing...");
    Serial.printf("   - Size: %dx%d\n", cols, rows);
    
    lcd.init();
    lcd.backlight();
    lcd.clear();
    
    // Test display
    lcd.setCursor(0, 0);
    lcd.print("SMART DOORLOCK");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    
    Serial.println("✅ LCD_Driver: Ready");
}

void LCD_Driver::clear() {
    lcd.clear();
}

void LCD_Driver::backlightOn() {
    lcd.backlight();
}

void LCD_Driver::backlightOff() {
    lcd.noBacklight();
}

void LCD_Driver::setCursor(uint8_t col, uint8_t row) {
    lcd.setCursor(col, row);
}

void LCD_Driver::print(const String& text) {
    lcd.print(text);
}

void LCD_Driver::printAt(uint8_t col, uint8_t row, const String& text) {
    lcd.setCursor(col, row);
    lcd.print(text);
}

void LCD_Driver::showMessage(const String& line1, const String& line2) {
    lcd.clear();
    
    // Center line 1 if shorter than display width
    uint8_t col1 = (line1.length() < cols) ? (cols - line1.length()) / 2 : 0;
    lcd.setCursor(col1, 0);
    lcd.print(line1.substring(0, cols));
    
    // Center line 2 if shorter than display width
    if (line2.length() > 0) {
        uint8_t col2 = (line2.length() < cols) ? (cols - line2.length()) / 2 : 0;
        lcd.setCursor(col2, 1);
        lcd.print(line2.substring(0, cols));
    }
}

void LCD_Driver::showMessageTimed(const String& line1, const String& line2, uint16_t duration_ms) {
    showMessage(line1, line2);
    delay(duration_ms);
}