// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Keypad/Keypad_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "Keypad_Driver.h"

// Keypad layout
const char KEYS[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Pin definitions (from Config.h)
byte ROW_PINS[4] = {33, 32, 4, 15};
byte COL_PINS[4] = {26, 25, 17, 16};

Keypad_Driver::Keypad_Driver() : lastKey('\0'), lastPressTime(0) {
    keypad = new Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, 4, 4);
}

Keypad_Driver::~Keypad_Driver() {
    delete keypad;
}

void Keypad_Driver::init() {
    Serial.println("🔧 Keypad_Driver: Initializing...");
    Serial.println("   - Layout: 4x4 matrix");
    Serial.println("   - Keys: 0-9, A-D, *, #");
    Serial.println("✅ Keypad_Driver: Ready");
}

char Keypad_Driver::getKey() {
    char key = keypad->getKey();
    
    if (key) {
        // Debounce: ignore same key within debounce time
        unsigned long now = millis();
        if (key == lastKey && (now - lastPressTime) < DEBOUNCE_TIME) {
            return '\0';
        }
        
        lastKey = key;
        lastPressTime = now;
        
        Serial.printf("⌨️  Keypad: Key pressed [%c]\n", key);
        return key;
    }
    
    return '\0';
}

bool Keypad_Driver::isPressed() {
    return (keypad->getKey() != '\0');
}

char Keypad_Driver::waitForKey(uint16_t timeout_ms) {
    unsigned long start = millis();
    
    while (true) {
        char key = getKey();
        if (key != '\0') {
            return key;
        }
        
        if (timeout_ms > 0 && (millis() - start) >= timeout_ms) {
            return '\0';
        }
        
        delay(10);
    }
}