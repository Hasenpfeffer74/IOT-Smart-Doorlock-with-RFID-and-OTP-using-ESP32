// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/LED/LED_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "LED_Driver.h"

LED_Driver::LED_Driver(uint8_t led_pin) : pin(led_pin), state(false) {
}

void LED_Driver::init() {
    Serial.println("🔧 LED_Driver: Initializing...");
    Serial.printf("   - Pin: GPIO %d\n", pin);
    
    off();
    
    // Test blink
    blink(2, 150);
    
    Serial.println("✅ LED_Driver: Ready");
}

void LED_Driver::on() {
    digitalWrite(pin, HIGH);
    state = true;
}

void LED_Driver::off() {
    digitalWrite(pin, LOW);
    state = false;
}

void LED_Driver::toggle() {
    state = !state;
    digitalWrite(pin, state ? HIGH : LOW);
}

bool LED_Driver::isOn() const {
    return state;
}

void LED_Driver::blink(uint8_t times, uint16_t delay_ms) {
    for (uint8_t i = 0; i < times; i++) {
        on();
        delay(delay_ms);
        off();
        
        if (i < times - 1) {
            delay(delay_ms);
        }
    }
}

void LED_Driver::blinkContinuous(uint16_t duration_ms, uint16_t delay_ms) {
    unsigned long start = millis();
    
    while (millis() - start < duration_ms) {
        toggle();
        delay(delay_ms);
    }
    
    off();
}