// ═══════════════════════════════════════════════════════════
// FILE: src/App/OTPManager/OTPManager.h
// ═══════════════════════════════════════════════════════════
#ifndef OTPMANAGER_H
#define OTPMANAGER_H

#include <Arduino.h>
#include "../TelegramNotifier/TelegramNotifier.h"
#include "../../Drivers/LCD/LCD_Driver.h"
#include "../../Config.h"  // Add this to use OTP_LENGTH and OTP_EXPIRE_TIME macros

/**
 * @brief One-Time Password Manager
 * @details Generates, validates, and manages OTP lifecycle
 */
class OTPManager {
public:
    OTPManager(TelegramNotifier* telegram_notifier, LCD_Driver* lcd_driver);
    
    /**
     * @brief Initialize OTP manager
     */
    void init();
    
    /**
     * @brief Generate new OTP and send via Telegram
     * @return true if generated and sent successfully
     */
    bool generateOTP();
    
    /**
     * @brief Add digit to input buffer
     * @param digit Digit character (0-9)
     * @return true if buffer is full (ready to verify)
     */
    bool addDigit(char digit);
    
    /**
     * @brief Verify entered OTP
     * @param otp OTP to verify
     * @return 1 if valid, -1 if wrong, -3 if expired
     */
    int verify(int otp);
    
    /**
     * @brief Check if OTP is expired
     * @return true if expired, false otherwise
     */
    bool isExpired();
    
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
     * @brief Reset OTP (clear OTP and input)
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
    
private:
    int generatedOTP;
    unsigned long otpGeneratedTime;
    String inputBuffer;
    TelegramNotifier* telegram;
    LCD_Driver* lcd;
};

#endif // OTPMANAGER_H
