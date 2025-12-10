// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_I2C.cpp
// ═══════════════════════════════════════════════════════════
#include "BSP_I2C.h"

bool BSP_I2C::initialized = false;
int BSP_I2C::sda = 21;
int BSP_I2C::scl = 22;

void BSP_I2C::init(int sda_pin, int scl_pin, uint32_t frequency) {
    if (initialized) {
        Serial.println("⚠️  BSP_I2C: Already initialized");
        return;
    }
    
    sda = sda_pin;
    scl = scl_pin;
    
    Serial.println("🔧 BSP_I2C: Initializing I2C bus...");
    Serial.printf("   - SDA: GPIO %d\n", sda);
    Serial.printf("   - SCL: GPIO %d\n", scl);
    Serial.printf("   - Frequency: %d Hz\n", frequency);
    
    // Initialize I2C with custom pins and frequency
    Wire.begin(sda, scl, frequency);
    
    initialized = true;
    Serial.println("✅ BSP_I2C: Initialization complete");
    
    // Optional: Scan for devices
    delay(100);
    scanDevices();
}

TwoWire* BSP_I2C::getInstance() {
    if (!initialized) {
        Serial.println("❌ BSP_I2C: Not initialized! Call init() first.");
        return nullptr;
    }
    return &Wire;
}

bool BSP_I2C::isInitialized() {
    return initialized;
}

void BSP_I2C::scanDevices() {
    Serial.println("🔍 BSP_I2C: Scanning I2C bus...");
    
    byte count = 0;
    for (byte addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.printf("   ✅ Device found at 0x%02X\n", addr);
            count++;
        }
    }
    
    if (count == 0) {
        Serial.println("   ❌ No I2C devices found!");
    } else {
        Serial.printf("   Found %d device(s)\n", count);
    }
}