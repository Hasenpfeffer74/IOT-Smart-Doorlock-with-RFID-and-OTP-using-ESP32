// ═══════════════════════════════════════════════════════════
// FILE: src/App/TelegramNotifier/TelegramNotifier.h
// ═══════════════════════════════════════════════════════════
#ifndef TELEGRAM_NOTIFIER_H
#define TELEGRAM_NOTIFIER_H

#include <Arduino.h>
#include <HTTPClient.h>
#include "App/WiFiManager/WiFiManager.h"

/**
 * @brief Telegram Bot Notification System
 * @details Sends messages to Telegram chat via Bot API
 */
class TelegramNotifier {
private:
    String botToken;
    String chatId;
    WiFiManager* wifi;
    bool enabled;

public:
    /**
     * @brief Constructor
     * @param bot_token Telegram Bot Token
     * @param chat_id Telegram Chat ID
     * @param wifi_mgr Pointer to WiFiManager instance
     */
    TelegramNotifier(const String& bot_token, const String& chat_id, WiFiManager* wifi_mgr);
    
    /**
     * @brief Initialize Telegram notifier
     */
    void init();
    
    /**
     * @brief Send message to Telegram
     * @param message Message text (supports emoji)
     * @return true if sent successfully, false otherwise
     */
    bool sendMessage(const String& message);
    
    /**
     * @brief Send unlock notification
     * @param method Unlock method (RFID/OTP/PASSWORD)
     */
    void sendUnlockNotification(const String& method);
    
    /**
     * @brief Send access denied alert
     * @param reason Denial reason
     */
    void sendAccessDeniedAlert(const String& reason);
    
    /**
     * @brief Send OTP code
     * @param otp OTP code (6 digits)
     */
    void sendOTP(int otp);
    
    /**
     * @brief Enable/disable notifications
     * @param enable true to enable, false to disable
     */
    void setEnabled(bool enable);
    
    /**
     * @brief Check if notifications are enabled
     * @return true if enabled, false otherwise
     */
    bool isEnabled() const;

private:
    /**
     * @brief URL encode string for HTTP GET
     * @param str String to encode
     * @return Encoded string
     */
    String urlEncode(const String& str);
};

#endif // TELEGRAM_NOTIFIER_H