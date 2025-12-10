// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Lock/Lock_Driver.cpp
// ═══════════════════════════════════════════════════════════
#include "Lock_Driver.h"

Lock_Driver::Lock_Driver(uint8_t lock_pin, bool active_low, bool reverse)
    : pin(lock_pin), locked(true), relayActiveLow(active_low), solenoidReverse(reverse) {
}

void Lock_Driver::init() {
    Serial.println("🔧 Lock_Driver: Initializing...");
    Serial.printf("   - Pin: GPIO %d\n", pin);
    Serial.printf("   - Relay: Active %s\n", relayActiveLow ? "LOW" : "HIGH");
    Serial.printf("   - Solenoid: %s\n", solenoidReverse ? "Reverse logic" : "Normal logic");
    
    // Set initial locked state
    lock();
    
    Serial.println("✅ Lock_Driver: Ready (LOCKED)");
}

void Lock_Driver::unlock() {
    if (solenoidReverse) {
        digitalWrite(pin, relayActiveLow ? LOW : HIGH);
    } else {
        digitalWrite(pin, relayActiveLow ? LOW : HIGH);
    }
    
    locked = false;
    Serial.println("🔓 Lock: UNLOCKED");
}

void Lock_Driver::lock() {
    if (solenoidReverse) {
        digitalWrite(pin, relayActiveLow ? HIGH : LOW);
    } else {
        digitalWrite(pin, relayActiveLow ? HIGH : LOW);
    }
    
    locked = true;
    Serial.println("🔒 Lock: LOCKED");
}

bool Lock_Driver::isLocked() const {
    return locked;
}

void Lock_Driver::toggle() {
    if (locked) {
        unlock();
    } else {
        lock();
    }
}