// ═══════════════════════════════════════════════════════════
// FILE: src/App/WiFiManager/WiFiManager.h
// ═══════════════════════════════════════════════════════════
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFi.h>

/**
 * @brief WiFi Connection Manager
 * @details Handles WiFi connection, reconnection, and status monitoring
 */
class WiFiManager {
private:
    String ssid;
    String password;
    bool connected;
    unsigned long lastConnectAttempt;
    uint8_t connectAttempts;
    
    static const uint16_t RECONNECT_INTERVAL = 30000; // 30 seconds
    static const uint8_t MAX_CONNECT_ATTEMPTS = 20;

public:
    /**
     * @brief Constructor
     * @param wifi_ssid WiFi SSID
     * @param wifi_pass WiFi password
     */
    WiFiManager(const String& wifi_ssid, const String& wifi_pass);
    
    /**
     * @brief Initialize and connect to WiFi
     * @return true if connected, false otherwise
     */
    bool init();
    
    /**
     * @brief Connect to WiFi (blocking with timeout)
     * @param timeout_ms Connection timeout in milliseconds
     * @return true if connected, false if timeout
     */
    bool connect(uint16_t timeout_ms = 10000);
    
    /**
     * @brief Check if WiFi is connected
     * @return true if connected, false otherwise
     */
    bool isConnected();
    
    /**
     * @brief Reconnect if disconnected (non-blocking)
     * @note Call this in loop() to auto-reconnect
     */
    void maintain();
    
    /**
     * @brief Disconnect from WiFi
     */
    void disconnect();
    
    /**
     * @brief Get IP address
     * @return IP address as String, empty if not connected
     */
    String getIP();
    
    /**
     * @brief Get signal strength (RSSI)
     * @return RSSI in dBm
     */
    int getRSSI();
};

#endif // WIFI_MANAGER_H