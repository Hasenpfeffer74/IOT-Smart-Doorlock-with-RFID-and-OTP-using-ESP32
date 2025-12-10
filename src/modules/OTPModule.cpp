// ═══════════════════════════════════════════════════════════
// FILE: OTPModule.cpp
// ═══════════════════════════════════════════════════════════

#include "OTPModule.h"

OTPModule::OTPModule() {
  generatedOTP = 0;
  otpTime = 0;
  inputBuffer = "";
}

void OTPModule::init() {
  connectWiFi();
  randomSeed(analogRead(0));
}

void OTPModule::connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  
  Serial.print("Connecting to WiFi");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(300);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Connected!");
  } else {
    Serial.println(" Failed!");
  }
}

void OTPModule::generateOTP(LiquidCrystal_I2C* lcd) {
  generatedOTP = random(100000, 999999);
  otpTime = millis();

  lcd->clear();
  lcd->print("Sending OTP...");
  
  // Debug info
  Serial.print("WiFi Status: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");
  Serial.print("Generated OTP: ");
  Serial.println(generatedOTP);
  
  // Send via Telegram
  String message = "🔐 Door OTP: " + String(generatedOTP) + "\nValid for 60s";
  sendTelegramMessage(message);
  
  lcd->clear();
  lcd->print("OTP Sent!");
  delay(3000);
}

void OTPModule::showInputScreen(LiquidCrystal_I2C* lcd) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Enter OTP:");
  lcd->setCursor(0, 1);
  lcd->print("> ");
  inputBuffer = "";
}

int OTPModule::handleInput(char key, LiquidCrystal_I2C* lcd) {
  if (key >= '0' && key <= '9') {
    if (inputBuffer.length() < OTP_LENGTH) {
      inputBuffer += key;
      lcd->setCursor(2 + inputBuffer.length() - 1, 1);
      lcd->print("*");
    }
    
    if (inputBuffer.length() == OTP_LENGTH) {
      delay(300);
      int userOTP = inputBuffer.toInt();
      
      if (millis() - otpTime > OTP_EXPIRE_TIME) {
        sendTelegramMessage("⏱️ OTP expired");
        reset();
        return -3;  // Display error handled by lock control
      }
      else if (userOTP == generatedOTP) {
        reset();
        return 1;
      }
      else {
        sendTelegramMessage("⚠️ Failed OTP attempt");
        reset();
        return -1;  //  Display error handled by lock control
      }
    }
  }
  else if (key == '*') {
    showInputScreen(lcd);
  }
  else if (key == 'D') {
    reset();
    return -2;
  }
  
  return 0;
}

void OTPModule::sendTelegramMessage(String msg) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ WiFi not connected!");
    return;
  }

  // URL encode the message
  msg.replace(" ", "%20");
  msg.replace("\n", "%0A");
  msg.replace("🔐", "");
  msg.replace("⚠️", "");
  msg.replace("⏱️", "");

  String url = "https://api.telegram.org/bot" + String(BOT_TOKEN) +
               "/sendMessage?chat_id=" + String(CHAT_ID) +
               "&text=" + msg;

  Serial.println("Sending to Telegram...");
  Serial.println("URL: " + url);

  HTTPClient http;
  http.begin(url);
  http.setTimeout(10000); // 10 second timeout
  
  int httpCode = http.GET();
  
  Serial.print("Telegram Response Code: ");
  Serial.println(httpCode);
  
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
  } else {
    Serial.println("❌ HTTP Error: " + http.errorToString(httpCode));
  }
  
  http.end();
}

void OTPModule::reset() {
  inputBuffer = "";
  generatedOTP = 0;
}