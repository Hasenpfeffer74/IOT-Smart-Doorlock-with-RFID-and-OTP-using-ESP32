// ═══════════════════════════════════════════════════════════
// FILE: src/BSP/BSP_GPIO.cpp
// ═══════════════════════════════════════════════════════════
#include "BSP_GPIO.h"

// Pin definitions from Config
#define LOCK_PIN    2
#define LED_PIN     14
#define BUZZER_PIN  27

// Keypad pins
#define KEYPAD_ROW_1  33
#define KEYPAD_ROW_2  32
#define KEYPAD_ROW_3  4
#define KEYPAD_ROW_4  15

#define KEYPAD_COL_1  26
#define KEYPAD_COL_2  25
#define KEYPAD_COL_3  17
#define KEYPAD_COL_4  16

bool BSP_GPIO::initialized = false;

void BSP_GPIO::init() {
    if (initialized) {
        Serial.println("⚠️  BSP_GPIO: Already initialized");
        return;
    }
    
    Serial.println("🔧 BSP_GPIO: Initializing GPIO pins...");
    
    initOutputPins();
    initInputPins();
    
    initialized = true;
    Serial.println("✅ BSP_GPIO: Initialization complete");
    
    printConfig();
}

void BSP_GPIO::initOutputPins() {
    Serial.println("   📤 Configuring OUTPUT pins:");
    
    // Lock Control (Relay)
    pinMode(LOCK_PIN, OUTPUT);
    digitalWrite(LOCK_PIN, HIGH); // Relay active LOW, so HIGH = locked
    Serial.printf("      - LOCK:   GPIO %d (Relay)\n", LOCK_PIN);
    
    // LED Indicator
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // LED off initially
    Serial.printf("      - LED:    GPIO %d\n", LED_PIN);
    
    // Buzzer
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW); // Buzzer off initially
    Serial.printf("      - BUZZER: GPIO %d\n", BUZZER_PIN);
}

void BSP_GPIO::initInputPins() {
    Serial.println("   📥 Configuring INPUT pins (Keypad):");
    
    // Keypad rows (output from keypad perspective, but we scan them)
    pinMode(KEYPAD_ROW_1, INPUT);
    pinMode(KEYPAD_ROW_2, INPUT);
    pinMode(KEYPAD_ROW_3, INPUT);
    pinMode(KEYPAD_ROW_4, INPUT);
    
    Serial.printf("      - Rows: GPIO %d, %d, %d, %d\n", 
                  KEYPAD_ROW_1, KEYPAD_ROW_2, KEYPAD_ROW_3, KEYPAD_ROW_4);
    
    // Keypad columns (input from keypad perspective)
    pinMode(KEYPAD_COL_1, INPUT_PULLUP);
    pinMode(KEYPAD_COL_2, INPUT_PULLUP);
    pinMode(KEYPAD_COL_3, INPUT_PULLUP);
    pinMode(KEYPAD_COL_4, INPUT_PULLUP);
    
    Serial.printf("      - Cols: GPIO %d, %d, %d, %d\n", 
                  KEYPAD_COL_1, KEYPAD_COL_2, KEYPAD_COL_3, KEYPAD_COL_4);
}

bool BSP_GPIO::isInitialized() {
    return initialized;
}

void BSP_GPIO::printConfig() {
    Serial.println("\n╔═══════════════════════════════════════╗");
    Serial.println("║      GPIO CONFIGURATION SUMMARY       ║");
    Serial.println("╠═══════════════════════════════════════╣");
    Serial.printf("║ Lock Control:  GPIO %-2d (Relay)      ║\n", LOCK_PIN);
    Serial.printf("║ LED Indicator: GPIO %-2d               ║\n", LED_PIN);
    Serial.printf("║ Buzzer:        GPIO %-2d               ║\n", BUZZER_PIN);
    Serial.println("╠═══════════════════════════════════════╣");
    Serial.println("║ Keypad Matrix:                        ║");
    Serial.printf("║   Rows: %2d, %2d, %2d, %2d               ║\n", 
                  KEYPAD_ROW_1, KEYPAD_ROW_2, KEYPAD_ROW_3, KEYPAD_ROW_4);
    Serial.printf("║   Cols: %2d, %2d, %2d, %2d               ║\n", 
                  KEYPAD_COL_1, KEYPAD_COL_2, KEYPAD_COL_3, KEYPAD_COL_4);
    Serial.println("╚═══════════════════════════════════════╝\n");
}