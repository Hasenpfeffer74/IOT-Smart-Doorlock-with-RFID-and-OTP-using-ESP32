#include "Config.h"

// Define Keypad layout
const char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define Keypad pins
byte KEYPAD_ROW_PINS[KEYPAD_ROWS] = {33, 32, 4, 15};
byte KEYPAD_COL_PINS[KEYPAD_COLS] = {26, 25, 17, 16};