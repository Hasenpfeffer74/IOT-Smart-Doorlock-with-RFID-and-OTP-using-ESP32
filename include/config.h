// ═══════════════════════════════════════════════════════════
// FILE: include/Config.h
// ═══════════════════════════════════════════════════════════
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ═══════════════════════════════════════════════════════════
// HARDWARE PIN CONFIGURATION
// ═══════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────
// SPI Pins (RFID RC522)
// ─────────────────────────────────────────────────────────
#define RFID_SS_PIN     18      // SDA/SS
#define RFID_RST_PIN    13      // RST
#define RFID_SCK_PIN    19      // SCK
#define RFID_MISO_PIN   5       // MISO
#define RFID_MOSI_PIN   23      // MOSI

// ─────────────────────────────────────────────────────────
// I2C Pins (LCD 1602)
// ─────────────────────────────────────────────────────────
#define I2C_SDA_PIN     21      // SDA (ESP32 default)
#define I2C_SCL_PIN     22      // SCL (ESP32 default)
#define I2C_FREQUENCY   100000  // 100kHz

// ─────────────────────────────────────────────────────────
// GPIO Output Pins
// ─────────────────────────────────────────────────────────
#define LOCK_PIN        2       // Relay for Solenoid Lock
#define LED_PIN         14      // Status LED
#define BUZZER_PIN      27      // 5V Active Buzzer

// ─────────────────────────────────────────────────────────
// Keypad Matrix Pins (4x4)
// ─────────────────────────────────────────────────────────
#define KEYPAD_ROWS     4
#define KEYPAD_COLS     4

// Row pins (connect to keypad rows)
#define KEYPAD_ROW_1    33
#define KEYPAD_ROW_2    32
#define KEYPAD_ROW_3    4
#define KEYPAD_ROW_4    15

// Column pins (connect to keypad columns)
#define KEYPAD_COL_1    26
#define KEYPAD_COL_2    25
#define KEYPAD_COL_3    17
#define KEYPAD_COL_4    16

// ═══════════════════════════════════════════════════════════
// NETWORK CONFIGURATION
// ═══════════════════════════════════════════════════════════
#define WIFI_SSID       "YOUR WIFI SSID"    //Enter your WIFI name
#define WIFI_PASSWORD   "YOUR WIFI PASSWORD"  //Enter your WIFI password
#define WIFI_TIMEOUT    10000   // 10 seconds

/* ═══════════════════════════════════════════════════════════
 * TELEGRAM BOT CREDENTIALS
 * 
 * How to get Bot Token:
 * 1. Open Telegram, search @BotFather
 * 2. Send /newbot
 * 3. Follow instructions
 * 4. Copy the token
 * 
 * How to get Chat ID:
 * 1. Open Telegram, search @userinfobot
 * 2. Send /start
 * 3. Copy your ID number
 * ═══════════════════════════════════════════════════════════ */
#define BOT_TOKEN       "8311757423:AAFPZOz62SOHCWVKgkjBy4yBoguouTvL3Qg"
#define CHAT_ID         "1602072119"

// ═══════════════════════════════════════════════════════════
// SECURITY CONFIGURATION
// ═══════════════════════════════════════════════════════════

// ─────────────────────────────────────────────────────────
// Password Settings
// ─────────────────────────────────────────────────────────
#define DOOR_PASSWORD   "1234"
#define PASSWORD_LENGTH 4

// ─────────────────────────────────────────────────────────
// OTP Settings
// ─────────────────────────────────────────────────────────
#define OTP_LENGTH      6
#define OTP_EXPIRE_TIME 60000   // 60 seconds

/* ═══════════════════════════════════════════════════════════
 * RFID CARD UIDS
 * 
 * How to get UID:
 * 1. Upload RFID test sketch
 * 2. Scan your card
 * 3. Check Serial Monitor for UID
 * 4. Add UID to array below (format: "FA904A06")
 * ═══════════════════════════════════════════════════════════ */
const String VALID_RFID_UIDS[] = {
    "FA904A06"
    // Add more card UIDs here
    // "12345678",
    // "ABCDEF01"
};
const int VALID_RFID_COUNT = sizeof(VALID_RFID_UIDS) / sizeof(VALID_RFID_UIDS[0]);

// ═══════════════════════════════════════════════════════════
// LCD CONFIGURATION
// ═══════════════════════════════════════════════════════════
#define LCD_ADDRESS     0x27    // I2C address (try 0x3F if 0x27 doesn't work)
#define LCD_COLS        16
#define LCD_ROWS        2

// ═══════════════════════════════════════════════════════════
// LOCK CONTROL CONFIGURATION
// ═══════════════════════════════════════════════════════════
#define UNLOCK_DURATION 5000    // 5 seconds
#define RELAY_ACTIVE_LOW true   // true if relay activates on LOW
#define SOLENOID_REVERSE false  // false = needs power to UNLOCK

// ═══════════════════════════════════════════════════════════
// BUZZER PATTERNS
// ═══════════════════════════════════════════════════════════
#define BEEP_SUCCESS_DURATION   300     // ms
#define BEEP_ERROR_DURATION     200     // ms
#define BEEP_ERROR_PAUSE        200     // ms
#define BEEP_WARNING_DURATION   150     // ms
#define BEEP_WARNING_PAUSE      150     // ms

// ═══════════════════════════════════════════════════════════
// SYSTEM TIMING
// ═══════════════════════════════════════════════════════════
#define SCREEN_TIMEOUT  15000   // 15 seconds
#define SERIAL_BAUD     115200

// ═══════════════════════════════════════════════════════════
// KEYPAD LAYOUT
// ═══════════════════════════════════════════════════════════
const char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// ═══════════════════════════════════════════════════════════
// DEBUG CONFIGURATION
// ═══════════════════════════════════════════════════════════
#define DEBUG_MODE      true    // Enable/disable debug prints
#define DEBUG_RFID      true
#define DEBUG_KEYPAD    true
#define DEBUG_WIFI      true
#define DEBUG_TELEGRAM  true

// ═══════════════════════════════════════════════════════════
// VERSION INFO
// ═══════════════════════════════════════════════════════════
#define FIRMWARE_VERSION "2.0.0"
#define PROJECT_NAME     "Smart Doorlock System"
#define AUTHOR           "Nhom3"
#define BUILD_DATE       __DATE__
#define BUILD_TIME       __TIME__

#endif // CONFIG_H