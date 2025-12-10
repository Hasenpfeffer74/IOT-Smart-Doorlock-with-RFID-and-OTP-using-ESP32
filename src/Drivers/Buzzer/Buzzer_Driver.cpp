// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Buzzer/Buzzer_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "Buzzer_Driver.h"

Buzzer_Driver::Buzzer_Driver(uint8_t buzzer_pin) : pin(buzzer_pin), enabled(true) {
}

void Buzzer_Driver::init() {
    Serial.println("🔧 Buzzer_Driver: Initializing...");
    Serial.printf("   - Pin: GPIO %d\n", pin);
    
    off();
    
    // Test beep
    beep(100);
    
    Serial.println("✅ Buzzer_Driver: Ready");
}

void Buzzer_Driver::setEnabled(bool enable) {
    enabled = enable;
    Serial.printf("🔊 Buzzer: %s\n", enable ? "Enabled" : "Disabled");
}

void Buzzer_Driver::on() {
    if (enabled) {
        digitalWrite(pin, HIGH);
    }
}

void Buzzer_Driver::off() {
    digitalWrite(pin, LOW);
}

void Buzzer_Driver::beep(uint16_t duration_ms) {
    if (!enabled) return;
    
    on();
    delay(duration_ms);
    off();
}

void Buzzer_Driver::beepSuccess() {
    beep(300);
}

void Buzzer_Driver::beepError() {
    beepPattern(2, 200, 200);
}

void Buzzer_Driver::beepWarning() {
    beepPattern(3, 150, 150);
}

void Buzzer_Driver::beepPattern(uint8_t times, uint16_t duration_ms, uint16_t pause_ms) {
    if (!enabled) return;
    
    for (uint8_t i = 0; i < times; i++) {
        on();
        delay(duration_ms);
        off();
        
        if (i < times - 1) {
            delay(pause_ms);
        }
    }
}