// ═══════════════════════════════════════════════════════════
// FILE: src/App/OTPManager/OTPManager.cpp
// ═══════════════════════════════════════════════════════════
#include "OTPManager.h"

OTPManager::OTPManager(TelegramNotifier* telegram_notifier, LCD_Driver* lcd_driver)
    : generatedOTP(0), otpGeneratedTime(0), telegram(telegram_notifier), lcd(lcd_driver) {
}

void OTPManager::init() {
    Serial.println("🔧 OTPManager: Initializing...");
    Serial.printf("   - OTP Length: %d digits\n", OTP_LENGTH);
    Serial.printf("   - Expire Time: %d seconds\n", OTP_EXPIRE_TIME / 1000);
    randomSeed(analogRead(0));
    Serial.println("✅ OTPManager: Ready");
}

bool OTPManager::generateOTP() {
    // Generate 6-digit OTP
    generatedOTP = random(100000, 999999);
    otpGeneratedTime = millis();

    Serial.printf("🔐 OTP: Generated %06d\n", generatedOTP);

    // Show on LCD
    lcd->showMessage("Generating OTP...", "Please wait...");
    delay(500);

    // Send via Telegram (sendOTP returns void)
    telegram->sendOTP(generatedOTP);

    lcd->showMessageTimed("OTP Sent!", "Check Telegram", 2000);
    return true;
}

bool OTPManager::addDigit(char digit) {
    if (digit >= '0' && digit <= '9' && inputBuffer.length() < OTP_LENGTH) {
        inputBuffer += digit;
        updateInputDisplay();
        
        // Return true if buffer is full
        return (inputBuffer.length() == OTP_LENGTH);
    }
    return false;
}

int OTPManager::verify(int otp) {
    if (generatedOTP == 0) {
        Serial.println("❌ OTP: No OTP generated");
        return -1;
    }
    
    if (isExpired()) {
        Serial.println("⏱️ OTP: Expired");
        telegram->sendMessage("⏱️ OTP expired");
        reset();
        return -3;
    }
    
    if (otp == generatedOTP) {
        Serial.println("✅ OTP: Valid");
        reset();
        return 1;
    }
    
    Serial.println("❌ OTP: Invalid");
    telegram->sendAccessDeniedAlert("Wrong OTP entered");
    reset();
    return -1;
}

bool OTPManager::isExpired() {
    if (generatedOTP == 0) return true;
    return (millis() - otpGeneratedTime) > OTP_EXPIRE_TIME;
}

String OTPManager::getInputBuffer() const {
    return inputBuffer;
}

uint8_t OTPManager::getInputLength() const {
    return inputBuffer.length();
}

void OTPManager::clearInput() {
    inputBuffer = "";
}

void OTPManager::reset() {
    generatedOTP = 0;
    otpGeneratedTime = 0;
    clearInput();
}

void OTPManager::showInputScreen() {
    lcd->clear();
    lcd->printAt(0, 0, "Enter OTP:");
    lcd->printAt(0, 1, "> ");
    inputBuffer = "";
}

void OTPManager::updateInputDisplay() {
    lcd->setCursor(2, 1);
    // Show asterisks for entered digits
    for (uint8_t i = 0; i < inputBuffer.length(); i++) {
        lcd->print("*");
    }
    // Clear remaining positions
    for (uint8_t i = inputBuffer.length(); i < OTP_LENGTH; i++) {
        lcd->print(" ");
    }
}
