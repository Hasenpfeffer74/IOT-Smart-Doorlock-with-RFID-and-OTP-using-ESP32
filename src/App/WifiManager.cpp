// ═══════════════════════════════════════════════════════════
// FILE: src/App/WiFiManager/WiFiManager.cpp
// ═══════════════════════════════════════════════════════════
#include "WiFiManager.h"

WiFiManager::WiFiManager(const String& wifi_ssid, const String& wifi_pass)
    : ssid(wifi_ssid), password(wifi_pass), connected(false), 
      lastConnectAttempt(0), connectAttempts(0) {
}

bool WiFiManager::init() {
    Serial.println("🔧 WiFiManager: Initializing...");
    Serial.printf("   - SSID: %s\n", ssid.c_str());
    
    WiFi.mode(WIFI_STA);
    return connect();
}

bool WiFiManager::connect(uint16_t timeout_ms) {
    Serial.print("📡 WiFi: Connecting");
    
    WiFi.begin(ssid.c_str(), password.c_str());
    
    unsigned long start = millis();
    connectAttempts = 0;
    
    while (WiFi.status() != WL_CONNECTED && connectAttempts < MAX_CONNECT_ATTEMPTS) {
        if (millis() - start > timeout_ms) {
            Serial.println(" ❌ Timeout!");
            connected = false;
            return false;
        }
        
        delay(500);
        Serial.print(".");
        connectAttempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        connected = true;
        Serial.println(" ✅ Connected!");
        Serial.printf("   - IP: %s\n", WiFi.localIP().toString().c_str());
        Serial.printf("   - RSSI: %d dBm\n", WiFi.RSSI());
        return true;
    }
    
    Serial.println(" ❌ Failed!");
    connected = false;
    return false;
}

bool WiFiManager::isConnected() {
    connected = (WiFi.status() == WL_CONNECTED);
    return connected;
}

void WiFiManager::maintain() {
    if (!isConnected()) {
        unsigned long now = millis();
        if (now - lastConnectAttempt > RECONNECT_INTERVAL) {
            Serial.println("📡 WiFi: Reconnecting...");
            lastConnectAttempt = now;
            connect(5000); // 5 second timeout for reconnect
        }
    }
}

void WiFiManager::disconnect() {
    WiFi.disconnect();
    connected = false;
    Serial.println("📡 WiFi: Disconnected");
}

String WiFiManager::getIP() {
    if (isConnected()) {
        return WiFi.localIP().toString();
    }
    return "";
}

int WiFiManager::getRSSI() {
    if (isConnected()) {
        return WiFi.RSSI();
    }
    return 0;
}