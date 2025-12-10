// ═══════════════════════════════════════════════════════════
// FILE: src/App/OTPManager/OTPManager.h
// ═══════════════════════════════════════════════════════════
#ifndef OTP_MANAGER_H
#define OTP_MANAGER_H

#include <Arduino.h>
#include "App/TelegramNotifier/TelegramNotifier.h"
#include "Drivers/LCD/LCD_Driver.h"

/**
 * @brief One-Time Password Manager
 * @details Generates, validates, and manages OTP lifecycle
 */
class OTPManager {
private:
    int generatedOTP;
    unsigned long otpGeneratedTime;
    String inputBuffer;
    TelegramNotifier* telegram;
    LCD_Driver* lcd;
    
    static const uint16_t OTP_LENGTH = 6;
    static const uint32_t OTP_EXPIRE_TIME = 60000; // 60 seconds

public:
    /**
     * @brief Constructor
     * @param telegram_notifier Pointer to TelegramNotifier
     * @param lcd_driver Pointer to LCD_Driver
     */
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
};

#endif // OTP_MANAGER_H