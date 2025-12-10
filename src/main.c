/**
 * @file main.c
 * @brief Smart Doorlock Main Application
 * @author Nhom3
 * @date 2025
 * 
 * Main entry point for IOT Smart Doorlock with RFID, OTP, and PIN authentication
 */
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <Keypad.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LiquidCrystal_I2C.h>

#include "Config.h"
#include "modules/RFIDModule.h"
#include "modules/OTPModule.h"
#include "modules/PasswordModule.h"
#include "modules/LockControl.h"

/* ═══════════════════════════════════════════════════════════
 * GLOBAL VARIABLES
 * ═══════════════════════════════════════════════════════════ */
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);
Keypad keypad = Keypad(makeKeymap(KEYPAD_KEYS), KEYPAD_ROW_PINS, KEYPAD_COL_PINS, KEYPAD_ROWS, KEYPAD_COLS);

RFIDModule rfidModule;
OTPModule otpModule;
PasswordModule passwordModule;
LockControl lockControl;

typedef enum {
  MODE_MAIN,
  MODE_PASSWORD_INPUT,
  MODE_OTP_INPUT
} SystemMode;

SystemMode currentMode = MODE_MAIN;
unsigned long lastActivity = 0;

/* ═══════════════════════════════════════════════════════════
 * FUNCTION DECLARATIONS
 * ═══════════════════════════════════════════════════════════ */
void showMainMenu(void);
void handleKeypadInput(char key);
void checkTimeout(void);
void showInfo(void);

/* ═══════════════════════════════════════════════════════════
 * SETUP FUNCTION
 * ═══════════════════════════════════════════════════════════ */
void setup() {
  Serial.begin(115200);
  delay(500);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART DOOR LOCK");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1500);

  lockControl.init();
  rfidModule.init();
  otpModule.init();
  passwordModule.init();

  Serial.println("System Ready!");
  showMainMenu();
}

/* ═══════════════════════════════════════════════════════════
 * LOOP FUNCTION
 * ═══════════════════════════════════════════════════════════ */
void loop() {
  checkTimeout();

  char key = keypad.getKey();
  
  if (key) {
    lastActivity = millis();
    handleKeypadInput(key);
  }

  if (currentMode == MODE_MAIN) {
    String uid = rfidModule.checkCard();
    if (uid != "") {
      if (rfidModule.isValidCard(uid)) {
        lockControl.unlock("RFID", &lcd, [](String msg){ 
          // Lambda function to send Telegram
          if (WiFi.status() != WL_CONNECTED) return;
          String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) +
                       "/sendMessage?chat_id=" + String(CHAT_ID) +
                       "&text=" + msg;
          HTTPClient http;
          http.begin(url);
          http.GET();
          http.end();
        });
      } else {
        lockControl.showAccessDenied(&lcd, "Invalid Card");
        otpModule.sendTelegramMessage("⚠️ Unknown RFID: " + uid);
        showMainMenu();
      }
    }
  }
}

/* ═══════════════════════════════════════════════════════════
 * CHECK TIMEOUT
 * ═══════════════════════════════════════════════════════════ */
void checkTimeout() {
  if (currentMode != MODE_MAIN && (millis() - lastActivity > SCREEN_TIMEOUT)) {
    currentMode = MODE_MAIN;
    passwordModule.reset();
    otpModule.reset();
    showMainMenu();
  }
}

/* ═══════════════════════════════════════════════════════════
 * SHOW MAIN MENU
 * ═══════════════════════════════════════════════════════════ */
void showMainMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("A=OTP B=Pass");
  lcd.setCursor(0, 1);
  lcd.print("C=RFID D=Info");
}

/* ═══════════════════════════════════════════════════════════
 * HANDLE KEYPAD INPUT
 * ═══════════════════════════════════════════════════════════ */
void handleKeypadInput(char key) {
  Serial.print("Key: ");
  Serial.println(key);

  if (currentMode == MODE_MAIN) {
    if (key == 'A') {
      otpModule.generateOTP(&lcd);
      currentMode = MODE_OTP_INPUT;
      otpModule.showInputScreen(&lcd);
    }
    else if (key == 'B') {
      currentMode = MODE_PASSWORD_INPUT;
      passwordModule.showInputScreen(&lcd);
    }
    else if (key == 'C') {
      lcd.clear();
      lcd.print("Scan RFID Card");
      lcd.setCursor(0, 1);
      lcd.print("Valid: ");
      lcd.print(rfidModule.getValidCardCount());
      delay(2000);
      showMainMenu();
    }
    else if (key == 'D') {
      showInfo();
    }
  }
  else if (currentMode == MODE_PASSWORD_INPUT) {
    int result = passwordModule.handleInput(key, &lcd);
    
    if (result == 1) {
      lockControl.unlock("PASSWORD", &lcd, [](String msg){ 
        if (WiFi.status() != WL_CONNECTED) return;
        String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) +
                     "/sendMessage?chat_id=" + String(CHAT_ID) +
                     "&text=" + msg;
        HTTPClient http;
        http.begin(url);
        http.GET();
        http.end();
      });
      currentMode = MODE_MAIN;
      showMainMenu();
    }
    else if (result == -1) {
      lockControl.showAccessDenied(&lcd, "Wrong Password!");
      otpModule.sendTelegramMessage("⚠️ Failed password attempt");
      currentMode = MODE_MAIN;
      showMainMenu();
    }
    else if (result == -2) {
      currentMode = MODE_MAIN;
      showMainMenu();
    }
  }
  else if (currentMode == MODE_OTP_INPUT) {
    int result = otpModule.handleInput(key, &lcd);
    
    if (result == 1) {
      lockControl.unlock("OTP", &lcd, [](String msg){ 
        if (WiFi.status() != WL_CONNECTED) return;
        String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) +
                     "/sendMessage?chat_id=" + String(CHAT_ID) +
                     "&text=" + msg;
        HTTPClient http;
        http.begin(url);
        http.GET();
        http.end();
      });
      currentMode = MODE_MAIN;
      showMainMenu();
    }
    else if (result == -1) {
      lockControl.showAccessDenied(&lcd, "Wrong OTP!");
      currentMode = MODE_MAIN;
      showMainMenu();
    }
    else if (result == -3) {
      lockControl.showAccessDenied(&lcd, "OTP Expired!");
      currentMode = MODE_MAIN;
      showMainMenu();
    }
    else if (result == -2) {
      currentMode = MODE_MAIN;
      showMainMenu();
    }
  }
}

/* ═══════════════════════════════════════════════════════════
 * SHOW INFO
 * ═══════════════════════════════════════════════════════════ */
void showInfo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID: ");
  lcd.print(rfidModule.getValidCardCount());
  lcd.print(" WiFi:");
  lcd.print(WiFi.status() == WL_CONNECTED ? "OK" : "X");
  lcd.setCursor(0, 1);
  lcd.print("Lock: ");
  lcd.print(lockControl.isLocked() ? "Locked" : "Open");
  delay(3000);
  showMainMenu();
}