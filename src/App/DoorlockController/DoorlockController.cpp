// ═══════════════════════════════════════════════════════════
// FILE: src/App/DoorlockController/DoorlockController.cpp
// ═══════════════════════════════════════════════════════════
#include "DoorlockController.h"

DoorlockController::DoorlockController(Lock_Driver* lock_driver, LED_Driver* led_driver,
                                       Buzzer_Driver* buzzer_driver, LCD_Driver* lcd_driver,
                                       TelegramNotifier* telegram_notifier)
    : lock(lock_driver), led(led_driver), buzzer(buzzer_driver), 
      lcd(lcd_driver), telegram(telegram_notifier) {
}

void DoorlockController::init() {
    Serial.println("🔧 DoorlockController: Initializing...");
    Serial.println("✅ DoorlockController: Ready");
}

void DoorlockController::unlockDoor(const String& method) {
    Serial.printf("🔓 Doorlock: Unlocking via %s\n", method.c_str());
    
    // Step 1: Show access granted on LCD
    lcd->showMessage("ACCESS GRANTED", "Opening...");
    
    // Step 2: Visual and audio feedback
    led->on();
    buzzer->beepSuccess();
    
    // Step 3: Unlock the door
    lock->unlock();
    
    // Step 4: Send Telegram notification
    telegram->sendUnlockNotification(method);
    
    // Step 5: Show countdown
    showCountdown(UNLOCK_DURATION / 1000);
    
    // Step 6: Lock the door again
    lockDoor();
    
    // Step 7: Feedback for locking
    buzzer->beepSuccess();
    led->off();
    
    // Step 8: Show locked status
    lcd->showMessageTimed("Door Locked", "System Ready", 1500);
}

void DoorlockController::lockDoor() {
    lock->lock();
    Serial.println("🔒 Doorlock: Locked");
}

void DoorlockController::showAccessDenied(const String& reason) {
    Serial.printf("❌ Access Denied: %s\n", reason.c_str());
    
    // Show on LCD
    lcd->showMessage("ACCESS DENIED", reason);
    
    // Visual and audio alert
    led->blink(3, 200);
    buzzer->beepError();
    
    // Send notification
    telegram->sendAccessDeniedAlert(reason);
    
    delay(2000);
}

void DoorlockController::showCountdown(uint8_t seconds) {
    for (uint8_t i = seconds; i > 0; i--) {
        lcd->setCursor(0, 1);
        lcd->print("Closing in: ");
        lcd->print(String(i));
        lcd->print("s ");
        delay(1000);
    }
}

bool DoorlockController::isLocked() const {
    return lock->isLocked();
}
