// ═══════════════════════════════════════════════════════════
// FILE: src/Drivers/Lock/Lock_Driver.h
// ═══════════════════════════════════════════════════════════
#ifndef LOCK_DRIVER_H
#define LOCK_DRIVER_H

#include <Arduino.h>

/**
 * @brief Solenoid Lock Driver (via Relay)
 * @details Controls 12V solenoid lock through relay module
 * 
 * Hardware: 5V Relay + 12V Solenoid Lock
 * Logic: Relay Active LOW (LOW = energized, HIGH = off)
 * Solenoid: Needs power to UNLOCK (retract bolt)
 */
class Lock_Driver {
private:
    uint8_t pin;
    bool locked;
    bool relayActiveLow;
    bool solenoidReverse;

public:
    /**
     * @brief Constructor
     * @param lock_pin GPIO pin for relay (default: 2)
     * @param active_low Relay trigger logic (default: true)
     * @param reverse Solenoid logic (default: false - needs power to unlock)
     */
    Lock_Driver(uint8_t lock_pin = 2, bool active_low = true, bool reverse = false);
    
    /**
     * @brief Initialize lock
     * @note Must call BSP_GPIO::init() BEFORE this
     */
    void init();
    
    /**
     * @brief Unlock door (energize solenoid)
     */
    void unlock();
    
    /**
     * @brief Lock door (de-energize solenoid)
     */
    void lock();
    
    /**
     * @brief Check if door is locked
     * @return true if locked, false if unlocked
     */
    bool isLocked() const;
    
    /**
     * @brief Toggle lock state
     */
    void toggle();
};

#endif // LOCK_DRIVER_H