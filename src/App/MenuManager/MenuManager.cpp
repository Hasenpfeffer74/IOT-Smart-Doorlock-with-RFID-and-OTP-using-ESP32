// ═══════════════════════════════════════════════════════════
// FILE: src/App/MenuManager/MenuManager.cpp
// ═══════════════════════════════════════════════════════════
#include "MenuManager.h"

MenuManager::MenuManager(LCD_Driver* lcd_driver, RFID_Driver* rfid_driver)
    : lcd(lcd_driver), rfid(rfid_driver) {
}

void MenuManager::init() {
    Serial.println("🔧 MenuManager: Initializing...");
    Serial.println("✅ MenuManager: Ready");
}

void MenuManager::showMainMenu() {
    lcd->clear();
    lcd->printAt(0, 0, "A=OTP B=Pass");
    lcd->printAt(0, 1, "C=RFID D=Info");
}

void MenuManager::showRFIDInfo() {
    lcd->clear();
    lcd->printAt(0, 0, "Scan RFID Card");
    lcd->setCursor(0, 1);
    lcd->print("Valid: ");
    lcd->print(String(rfid->getValidCardCount()));
    delay(2000);
    showMainMenu();
}

void MenuManager::showSystemInfo(bool wifi_connected, bool door_locked) {
    lcd->clear();
    
    // Line 1: RFID count and WiFi status
    lcd->setCursor(0, 0);
    lcd->print("RFID:");
    lcd->print(String(rfid->getValidCardCount()));
    lcd->print(" WiFi:");
    lcd->print(wifi_connected ? "OK" : "X");
    
    // Line 2: Door lock status
    lcd->setCursor(0, 1);
    lcd->print("Lock: ");
    lcd->print(door_locked ? "Locked" : "Open");
    
    delay(3000);
    showMainMenu();
}

void MenuManager::showWelcome() {
    lcd->showMessageTimed("SMART DOORLOCK", "Initializing...", 1500);
}

void MenuManager::showScanCardPrompt() {
    lcd->showMessage("Ready", "Scan card...");
}