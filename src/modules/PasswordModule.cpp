#include "PasswordModule.h"

PasswordModule::PasswordModule() {
  inputBuffer = "";
}

void PasswordModule::init() {
  Serial.println("Password Module Ready");
}

void PasswordModule::showInputScreen(LiquidCrystal_I2C* lcd) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Enter Password:");
  lcd->setCursor(0, 1);
  lcd->print("> ");
  inputBuffer = "";
}

void PasswordModule::displayMask(LiquidCrystal_I2C* lcd) {
  lcd->setCursor(2, 1);
  for (int i = 0; i < inputBuffer.length(); i++) {
    lcd->print("*");
  }
  for (int i = inputBuffer.length(); i < PASSWORD_LENGTH; i++) {
    lcd->print(" ");
  }
}

int PasswordModule::handleInput(char key, LiquidCrystal_I2C* lcd) {
  if (key == '#') {
    if (inputBuffer.length() == 0) return 0;
    
    if (inputBuffer == String(DOOR_PASSWORD)) {
      reset();
      return 1;
    } else {
      reset();
      return -1;  // Display error handled by lock control
    }
  }
  else if (key == '*') {
    showInputScreen(lcd);
  }
  else if (key >= '0' && key <= '9') {
    if (inputBuffer.length() < PASSWORD_LENGTH) {
      inputBuffer += key;
      displayMask(lcd);
    }
  }
  else if (key == 'D') {
    reset();
    return -2;
  }
  
  return 0;
}

void PasswordModule::reset() {
  inputBuffer = "";
}