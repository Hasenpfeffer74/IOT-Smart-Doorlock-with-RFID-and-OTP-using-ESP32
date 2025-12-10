// ═══════════════════════════════════════════════════════════
// FILE: LockControl.cpp
// ═══════════════════════════════════════════════════════════

#include "LockControl.h"

LockControl::LockControl() {
  locked = true;
}

void LockControl::init() {
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  
  #ifdef SOLENOID_REVERSE
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, LOW);
    #else
      digitalWrite(LOCK_PIN, HIGH);
    #endif
  #else
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, HIGH);
    #else
      digitalWrite(LOCK_PIN, LOW);
    #endif
  #endif
  
  locked = true;
  Serial.println("Lock Control Ready (LED + Buzzer enabled)");
  Serial.print("Lock Pin: GPIO ");
  Serial.println(LOCK_PIN);
  Serial.print("LED Pin: GPIO ");
  Serial.println(LED_PIN);
  Serial.print("Buzzer Pin: GPIO ");
  Serial.println(BUZZER_PIN);
}

void LockControl::beepSuccess() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(BEEP_SUCCESS_DURATION);
  digitalWrite(BUZZER_PIN, LOW);
}

void LockControl::beepError() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(BEEP_ERROR_DURATION);
    digitalWrite(BUZZER_PIN, LOW);
    if (i < 1) delay(BEEP_ERROR_PAUSE);
  }
}

void LockControl::ledOn() {
  digitalWrite(LED_PIN, HIGH);
}

void LockControl::ledOff() {
  digitalWrite(LED_PIN, LOW);
}

void LockControl::ledBlink(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN, LOW);
    if (i < times - 1) delay(delayMs);
  }
}

void LockControl::ledBlinkWithBuzzer(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    // Led and buzzer on
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(delayMs);
    
    // Led and buzzer off
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    
    // Delay 
    if (i < times - 1) delay(delayMs);
  }
}

void LockControl::unlock(String method, LiquidCrystal_I2C* lcd, void (*sendTelegramFunc)(String)) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("ACCESS GRANTED");
  lcd->setCursor(0, 1);
  lcd->print("Opening...");

  // Led on and buzzer beeps 1 time
  ledOn();
  beepSuccess();

  // Activate relay to solenoid lock
  #ifdef SOLENOID_REVERSE
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, HIGH);
    #else
      digitalWrite(LOCK_PIN, LOW);
    #endif
  #else
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, LOW);
    #else
      digitalWrite(LOCK_PIN, HIGH);
    #endif
  #endif
  
  locked = false;
  
  Serial.println("╔════════════════════════════╗");
  Serial.println("║   DOOR UNLOCKED!           ║");
  Serial.println("╚════════════════════════════╝");
  Serial.print("Method: ");
  Serial.println(method);
  
  // Send Telegram notification
  if (sendTelegramFunc != nullptr) {
    sendTelegramFunc("✅ Door unlocked via " + method);
  }
  
  // Display countdown
  for (int i = UNLOCK_DURATION / 1000; i > 0; i--) {
    lcd->setCursor(0, 1);
    lcd->print("Closing in: ");
    lcd->print(i);
    lcd->print("s ");
    delay(1000);
  }
  
  // Lock
  lock();
  
  // Led off and buzzer beep 1 time
  ledOff();
  beepSuccess();
  
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("Door Locked");
  lcd->setCursor(0, 1);
  lcd->print("System Ready");
  delay(1500);
}

void LockControl::lock() {
  // Activate relay release selonoid
  #ifdef SOLENOID_REVERSE
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, LOW);
    #else
      digitalWrite(LOCK_PIN, HIGH);
    #endif
  #else
    #ifdef RELAY_ACTIVE_LOW
      digitalWrite(LOCK_PIN, HIGH);
    #else
      digitalWrite(LOCK_PIN, LOW);
    #endif
  #endif
  
  locked = true;
  Serial.println("Door Locked");
}

bool LockControl::isLocked() {
  return locked;
}

void LockControl::showAccessDenied(LiquidCrystal_I2C* lcd, String reason) {
  lcd->clear();
  lcd->setCursor(0, 0);
  lcd->print("ACCESS DENIED");
  lcd->setCursor(0, 1);
  lcd->print(reason);
  
  // LED blink 3 times with buzzer
  ledBlinkWithBuzzer(3, 200);
  
  delay(2000);
}