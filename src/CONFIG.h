#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// ═══════════════════════════════════════════════════════════
// RFID CONFIG
// ═══════════════════════════════════════════════════════════
#define RFID_SS_PIN 18      // SDA 
#define RFID_RST_PIN 13      // RST
#define RFID_SCK_PIN 19     // SCK 
#define RFID_MISO_PIN 5     // MISO 
#define RFID_MOSI_PIN 23    // MOSI 
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
    "50C01361" // Card 1 - Example
    // "12345678",     // Card 2 - Uncomment and add your UID
    // "ABCDEF12",     // Card 3 - Uncomment and add your UID
};
const int VALID_RFID_COUNT = sizeof(VALID_RFID_UIDS) / sizeof(VALID_RFID_UIDS[0]);

// ═══════════════════════════════════════════════════════════
// WiFi & Telegram Config
// ═══════════════════════════════════════════════════════════
// Your WiFi Network Name
#define WIFI_SSID "YOUR_WIFI_SSID_HERE"

// Your WiFi Password
#define WIFI_PASS "YOUR_WIFI_PASSWORD_HERE"
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
#define BOT_TOKEN "8311757423:AAFPZOz62SOHCWVKgkjBy4yBoguouTvL3Qg"
#define CHAT_ID "1602072119"

// ═══════════════════════════════════════════════════════════
// Password Config
// ═══════════════════════════════════════════════════════════
#define DOOR_PASSWORD "1234" //Default Password
#define PASSWORD_LENGTH 4

// ═══════════════════════════════════════════════════════════
// OTP Config
// ═══════════════════════════════════════════════════════════
#define OTP_LENGTH 6
#define OTP_EXPIRE_TIME 60000

// ═══════════════════════════════════════════════════════════
// LCD Config
// ═══════════════════════════════════════════════════════════
#define LCD_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// ═══════════════════════════════════════════════════════════
// KEYPAD CONFIG - UPDATED PINS
// ═══════════════════════════════════════════════════════════
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

extern const char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS];
extern byte KEYPAD_ROW_PINS[KEYPAD_ROWS];    
extern byte KEYPAD_COL_PINS[KEYPAD_COLS];    

// ═══════════════════════════════════════════════════════════
// Lock Config
// ═══════════════════════════════════════════════════════════
#define LOCK_PIN 2
#define UNLOCK_DURATION 5000  // 5s unlock

// ═══════════════════════════════════════════════════════════
// Relay Config
// ═══════════════════════════════════════════════════════════
#define RELAY_ACTIVE_LOW true 

// ═══════════════════════════════════════════════════════════
// Solenoid Logic
// ═══════════════════════════════════════════════════════════
#define SOLENOID_REVERSE false
// ═══════════════════════════════════════════════════════════
// LED & Buzzer Config
// ═══════════════════════════════════════════════════════════
#define LED_PIN 14        
#define BUZZER_PIN 27       

// ═══════════════════════════════════════════════════════════
// Buzzer Patterns
// ═══════════════════════════════════════════════════════════
#define BEEP_SUCCESS_DURATION 300    
#define BEEP_ERROR_DURATION 200      
#define BEEP_ERROR_PAUSE 200         

// ═══════════════════════════════════════════════════════════
// System Config
// ═══════════════════════════════════════════════════════════
#define SCREEN_TIMEOUT 15000

#endif
