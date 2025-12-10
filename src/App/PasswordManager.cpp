// ═══════════════════════════════════════════════════════════
// FILE: src/App/PasswordManager/PasswordManager.cpp
// ═══════════════════════════════════════════════════════════
#include "PasswordManager.h"

PasswordManager::PasswordManager(const String& password, LCD_Driver* lcd_driver, uint8_t max_len)
    : correctPassword(password), lcd(lcd_driver), maxLength(max_len) {
}

void PasswordManager::init() {
    Serial.println("🔧 PasswordManager: Initializing...");
    Serial.printf("   - Password Length: %d digits\n", maxLength);
    Serial.println("✅ PasswordManager: Ready");
}

bool PasswordManager::addDigit(char digit) {
    if (digit >= '0' && digit <= '9' && inputBuffer.length() < maxLength) {
        inputBuffer += digit;
        updateInputDisplay();
        
        // Return true if buffer reaches max length
        return (inputBuffer.length() == maxLength);
    }
    return false;
}

bool PasswordManager::verify() {
    bool isCorrect = (inputBuffer == correctPassword);
    
    if (isCorrect) {
        Serial.println("✅ Password: Correct");
    } else {
        Serial.println("❌ Password: Incorrect");
    }
    
    return isCorrect;
}

String PasswordManager::getInputBuffer() const {
    return inputBuffer;
}

uint8_t PasswordManager::getInputLength() const {
    return inputBuffer.length();
}

void PasswordManager::clearInput() {
    inputBuffer = "";
}

void PasswordManager::reset() {
    clearInput();
}

void PasswordManager::showInputScreen() {
    lcd->clear();
    lcd->printAt(0, 0, "Enter Password:");
    lcd->printAt(0, 1, "> ");
    inputBuffer = "";
}

void PasswordManager::updateInputDisplay() {
    lcd->setCursor(2, 1);
    // Show asterisks for entered digits
    for (uint8_t i = 0; i < inputBuffer.length(); i++) {
        lcd->print("*");
    }
    // Clear remaining positions
    for (uint8_t i = inputBuffer.length(); i < maxLength; i++) {
        lcd->print(" ");
    }
}

void PasswordManager::changePassword(const String& new_password) {
    correctPassword = new_password;
    Serial.printf("🔑 Password changed to: %s\n", new_password.c_str());
}