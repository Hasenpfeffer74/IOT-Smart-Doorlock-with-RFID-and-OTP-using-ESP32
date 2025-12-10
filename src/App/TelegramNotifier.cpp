// ═══════════════════════════════════════════════════════════
// FILE: src/App/TelegramNotifier/TelegramNotifier.cpp
// ═══════════════════════════════════════════════════════════
#include "TelegramNotifier.h"

TelegramNotifier::TelegramNotifier(const String& bot_token, const String& chat_id, WiFiManager* wifi_mgr)
    : botToken(bot_token), chatId(chat_id), wifi(wifi_mgr), enabled(true) {
}

void TelegramNotifier::init() {
    Serial.println("🔧 TelegramNotifier: Initializing...");
    Serial.printf("   - Bot Token: %s\n", botToken.substring(0, 10).c_str() + String("..."));
    Serial.printf("   - Chat ID: %s\n", chatId.c_str());
    Serial.println("✅ TelegramNotifier: Ready");
}

bool TelegramNotifier::sendMessage(const String& message) {
    if (!enabled) {
        Serial.println("📱 Telegram: Disabled, message not sent");
        return false;
    }
    
    if (!wifi->isConnected()) {
        Serial.println("❌ Telegram: WiFi not connected!");
        return false;
    }
    
    // URL encode message
    String encodedMsg = urlEncode(message);
    
    // Build Telegram API URL
    String url = "https://api.telegram.org/bot" + botToken +
                 "/sendMessage?chat_id=" + chatId +
                 "&text=" + encodedMsg;
    
    Serial.println("📱 Telegram: Sending message...");
    
    HTTPClient http;
    http.begin(url);
    http.setTimeout(10000); // 10 second timeout
    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
        String payload = http.getString();
        Serial.printf("   - Response code: %d\n", httpCode);
        
        if (httpCode == 200) {
            Serial.println("   ✅ Message sent successfully!");
            http.end();
            return true;
        } else {
            Serial.printf("   ⚠️ HTTP error: %s\n", payload.c_str());
        }
    } else {
        Serial.printf("   ❌ Connection error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
    return false;
}

void TelegramNotifier::sendUnlockNotification(const String& method) {
    String emoji = "✅";
    String message = emoji + " Door Unlocked!\n"
                     "Method: " + method + "\n"
                     "Time: " + String(millis() / 1000) + "s";
    sendMessage(message);
}

void TelegramNotifier::sendAccessDeniedAlert(const String& reason) {
    String emoji = "⚠️";
    String message = emoji + " Access Denied!\n"
                     "Reason: " + reason + "\n"
                     "Time: " + String(millis() / 1000) + "s";
    sendMessage(message);
}

void TelegramNotifier::sendOTP(int otp) {
    String emoji = "🔐";
    String message = emoji + " Door Access OTP\n\n"
                     "Code: " + String(otp) + "\n"
                     "Valid for 60 seconds\n\n"
                     "Do not share this code!";
    sendMessage(message);
}

void TelegramNotifier::setEnabled(bool enable) {
    enabled = enable;
    Serial.printf("📱 Telegram: Notifications %s\n", enable ? "enabled" : "disabled");
}

bool TelegramNotifier::isEnabled() const {
    return enabled;
}

String TelegramNotifier::urlEncode(const String& str) {
    String encoded = "";
    char c;
    
    for (size_t i = 0; i < str.length(); i++) {
        c = str.charAt(i);
        
        if (c == ' ') {
            encoded += "%20";
        } else if (c == '\n') {
            encoded += "%0A";
        } else if (isAlphaNumeric(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c;
        } else {
            // Encode other characters
            encoded += '%';
            if (c < 0x10) encoded += '0';
            encoded += String(c, HEX);
        }
    }
    
    return encoded;
}