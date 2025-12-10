// ═══════════════════════════════════════════════════════════
// FILE: src/main.cpp
// ═══════════════════════════════════════════════════════════
/**
 * @file main.cpp
 * @brief Smart Doorlock Main Application
 * @author Nhom3
 * @version 2.0.0
 * @date 2025
 * 
 * @description
 * IoT Smart Doorlock with multiple authentication methods:
 * - RFID Card Authentication
 * - OTP (One-Time Password) via Telegram
 * - PIN Password Authentication
 */

#include <Arduino.h>
#include "Config.h"

// BSP Layer
#include "BSP/BSP_GPIO.h"
#include "BSP/BSP_SPI.h"
#include "BSP/BSP_I2C.h"

// Driver Layer
#include "Drivers/RFID/RFID_Driver.h"
#include "Drivers/LCD/LCD_Driver.h"
#include "Drivers/Keypad/Keypad_Driver.h"
#include "Drivers/Lock/Lock_Driver.h"
#include "Drivers/Buzzer/Buzzer_Driver.h"
#include "Drivers/LED/LED_Driver.h"

// Application Layer
#include "App/WiFiManager/WiFiManager.h"
#include "App/TelegramNotifier/TelegramNotifier.h"
#include "App/OTPManager/OTPManager.h"
#include "App/PasswordManager/PasswordManager.h"
#include "App/MenuManager/MenuManager.h"
#include "App/DoorlockController/DoorlockController.h"

// ═══════════════════════════════════════════════════════════
// GLOBAL OBJECTS
// ═══════════════════════════════════════════════════════════

// Driver Layer Instances
RFID_Driver rfid(RFID_SS_PIN, RFID_RST_PIN);
LCD_Driver lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
Keypad_Driver keypad;
Lock_Driver lock(LOCK_PIN, RELAY_ACTIVE_LOW, SOLENOID_REVERSE);
Buzzer_Driver buzzer(BUZZER_PIN);
LED_Driver led(LED_PIN);

// Application Layer Instances
WiFiManager wifi(WIFI_SSID, WIFI_PASSWORD);
TelegramNotifier telegram(BOT_TOKEN, CHAT_ID, &wifi);
OTPManager otpManager(&telegram, &lcd);
PasswordManager passwordManager(DOOR_PASSWORD, &lcd, PASSWORD_LENGTH);
MenuManager menu(&lcd, &rfid);
DoorlockController doorlock(&lock, &led, &buzzer, &lcd, &telegram);

// ═══════════════════════════════════════════════════════════
// SYSTEM STATE
// ═══════════════════════════════════════════════════════════

enum SystemMode {
    MODE_MAIN,          // Main menu - waiting for input
    MODE_PASSWORD,      // Password entry mode
    MODE_OTP           // OTP entry mode
};

SystemMode currentMode = MODE_MAIN;
unsigned long lastActivity = 0;

// ═══════════════════════════════════════════════════════════
// FUNCTION DECLARATIONS
// ═══════════════════════════════════════════════════════════

void printStartupBanner();
void initializeSystem();
void checkTimeout();
void handleKeyInput(char key);
void handleMainMenuInput(char key);
void handlePasswordInput(char key);
void handleOTPInput(char key);
void handleRFID();

// ═══════════════════════════════════════════════════════════
// SETUP FUNCTION
// ═══════════════════════════════════════════════════════════

void setup() {
    // Initialize Serial Communication
    Serial.begin(SERIAL_BAUD);
    delay(500);
    
    // Print startup banner
    printStartupBanner();
    
    // Initialize all system components
    initializeSystem();
    
    // Show welcome screen
    menu.showWelcome();
    
    // Show main menu
    menu.showMainMenu();
    
    // System ready
    Serial.println("");
    Serial.println("========================================");
    Serial.println("SYSTEM READY - WAITING FOR INPUT");
    Serial.println("========================================");
    Serial.println("");
    
    // Initial feedback
    led.blink(2, 150);
    buzzer.beep(100);
    
    // Reset activity timer
    lastActivity = millis();
}

// ═══════════════════════════════════════════════════════════
// MAIN LOOP
// ═══════════════════════════════════════════════════════════

void loop() {
    // Maintain WiFi connection
    wifi.maintain();
    
    // Check for timeout (return to main menu after inactivity)
    checkTimeout();
    
    // Handle keypad input
    char key = keypad.getKey();
    if (key) {
        lastActivity = millis();
        handleKeyInput(key);
    }
    
    // Handle RFID scanning (only in main mode)
    if (currentMode == MODE_MAIN) {
        handleRFID();
    }
    
    // Small delay to prevent CPU hogging
    delay(10);
}

// ═══════════════════════════════════════════════════════════
// INITIALIZATION FUNCTIONS
// ═══════════════════════════════════════════════════════════

void printStartupBanner() {
    Serial.println("");
    Serial.println("");
    Serial.println("========================================");
    Serial.println("                                        ");
    Serial.println("   SMART DOORLOCK SYSTEM v2.0           ");
    Serial.println("                                        ");
    Serial.println("   Multi-Authentication System          ");
    Serial.println("   IoT Telegram Integration             ");
    Serial.println("                                        ");
    Serial.println("========================================");
    Serial.println("   Author:  Nhom3");
    Serial.print("   Build:   ");
    Serial.print(__DATE__);
    Serial.print(" ");
    Serial.println(__TIME__);
    Serial.print("   Version: ");
    Serial.println(FIRMWARE_VERSION);
    Serial.println("========================================");
    Serial.println("");
}

void initializeSystem() {
    Serial.println("Starting System Initialization...");
    Serial.println("");
    
    // Initialize BSP Layer
    Serial.println("----------------------------------------");
    Serial.println("STEP 1: BSP Layer Initialization");
    Serial.println("----------------------------------------");
    
    BSP_GPIO::init();
    BSP_SPI::init();
    BSP_I2C::init();
    
    Serial.println("");
    
    // Initialize Driver Layer
    Serial.println("----------------------------------------");
    Serial.println("STEP 2: Driver Layer Initialization");
    Serial.println("----------------------------------------");
    
    rfid.init();
    lcd.init();
    keypad.init();
    lock.init();
    buzzer.init();
    led.init();
    
    Serial.println("");
    
    // Initialize Application Layer
    Serial.println("----------------------------------------");
    Serial.println("STEP 3: App Layer Initialization");
    Serial.println("----------------------------------------");
    
    wifi.init();
    telegram.init();
    otpManager.init();
    passwordManager.init();
    menu.init();
    doorlock.init();
    
    Serial.println("");
    Serial.println("All layers initialized successfully!");
    Serial.println("");
}

// ═══════════════════════════════════════════════════════════
// INPUT HANDLING FUNCTIONS
// ═══════════════════════════════════════════════════════════

void handleKeyInput(char key) {
    Serial.print("Key pressed: [");
    Serial.print(key);
    Serial.println("]");
    
    switch (currentMode) {
        case MODE_MAIN:
            handleMainMenuInput(key);
            break;
            
        case MODE_PASSWORD:
            handlePasswordInput(key);
            break;
            
        case MODE_OTP:
            handleOTPInput(key);
            break;
    }
}

void handleMainMenuInput(char key) {
    buzzer.beep(50);
    
    switch (key) {
        case 'A':
            Serial.println("Mode: OTP Authentication");
            if (otpManager.generateOTP()) {
                currentMode = MODE_OTP;
                otpManager.showInputScreen();
            } else {
                lcd.showMessageTimed("OTP Failed", "Check WiFi", 2000);
                menu.showMainMenu();
            }
            break;
            
        case 'B':
            Serial.println("Mode: Password Authentication");
            currentMode = MODE_PASSWORD;
            passwordManager.showInputScreen();
            break;
            
        case 'C':
            Serial.println("Showing RFID Info");
            menu.showRFIDInfo();
            break;
            
        case 'D':
            Serial.println("Showing System Info");
            menu.showSystemInfo(wifi.isConnected(), doorlock.isLocked());
            break;
            
        default:
            break;
    }
}

void handlePasswordInput(char key) {
    buzzer.beep(30);
    
    if (key == '#') {
        Serial.println("Verifying password...");
        if (passwordManager.verify()) {
            Serial.println("Password correct!");
            doorlock.unlockDoor("PASSWORD");
        } else {
            Serial.println("Password incorrect!");
            doorlock.showAccessDenied("Wrong Password");
            telegram.sendAccessDeniedAlert("Failed password attempt");
        }
        
        currentMode = MODE_MAIN;
        passwordManager.reset();
        menu.showMainMenu();
    }
    else if (key == '*') {
        Serial.println("Clearing password input");
        passwordManager.showInputScreen();
    }
    else if (key == 'D') {
        Serial.println("Password input cancelled");
        currentMode = MODE_MAIN;
        passwordManager.reset();
        menu.showMainMenu();
    }
    else if (key >= '0' && key <= '9') {
        passwordManager.addDigit(key);
    }
}

void handleOTPInput(char key) {
    buzzer.beep(30);
    
    if (key == '*') {
        Serial.println("Clearing OTP input");
        otpManager.showInputScreen();
    }
    else if (key == 'D') {
        Serial.println("OTP input cancelled");
        currentMode = MODE_MAIN;
        otpManager.reset();
        menu.showMainMenu();
    }
    else if (key >= '0' && key <= '9') {
        bool full = otpManager.addDigit(key);
        
        if (full) {
            Serial.println("Verifying OTP...");
            delay(300);
            
            int otp = otpManager.getInputBuffer().toInt();
            int result = otpManager.verify(otp);
            
            if (result == 1) {
                Serial.println("OTP valid!");
                doorlock.unlockDoor("OTP");
            } 
            else if (result == -3) {
                Serial.println("OTP expired!");
                doorlock.showAccessDenied("OTP Expired");
            } 
            else {
                Serial.println("OTP invalid!");
                doorlock.showAccessDenied("Wrong OTP");
            }
            
            currentMode = MODE_MAIN;
            menu.showMainMenu();
        }
    }
}

void handleRFID() {
    String uid = rfid.readCard();
    
    if (uid != "") {
        Serial.print("RFID Card detected: ");
        Serial.println(uid);
        
        if (rfid.isCardValid(uid)) {
            Serial.println("Valid RFID card!");
            doorlock.unlockDoor("RFID");
        } else {
            Serial.println("Invalid RFID card!");
            doorlock.showAccessDenied("Invalid Card");
            telegram.sendMessage("Unknown RFID card: " + uid);
        }
        
        menu.showMainMenu();
        lastActivity = millis();
    }
}

// ═══════════════════════════════════════════════════════════
// TIMEOUT HANDLING
// ═══════════════════════════════════════════════════════════

void checkTimeout() {
    if (currentMode != MODE_MAIN) {
        unsigned long now = millis();
        
        if (now - lastActivity > SCREEN_TIMEOUT) {
            Serial.println("");
            Serial.println("TIMEOUT: Returning to main menu");
            Serial.println("");
            
            currentMode = MODE_MAIN;
            passwordManager.reset();
            otpManager.reset();
            
            menu.showMainMenu();
            
            buzzer.beepWarning();
            led.blink(2, 100);
            
            lastActivity = millis();
        }
    }
}