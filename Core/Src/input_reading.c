/*
 * input_reading.c
 *
 *  Created on: Oct 21, 2024
 *      Author: phuct
 */

#include "main.h"
#include "input_reading.h"
#include "global.h"

// Timer interrupt duration is 10ms, so to pass 1 second, we need to jump to the interrupt service routine 100 times
#define DURATION_FOR_AUTO_INCREASING 	100
#define BUTTON_IS_PRESSED 				GPIO_PIN_RESET
#define BUTTON_IS_RELEASED 				GPIO_PIN_SET

// The buffers that store the final result after debouncing
static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState previousButtonBuffer[NO_OF_BUTTONS];

// We define three buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

// We define flags for button states
static uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint8_t flagForButtonPressShort[NO_OF_BUTTONS];


// Counter for automatically detecting when a button is pressed more than 1 second
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForLongPressInterval[NO_OF_BUTTONS];

void button_reading(void) {
    for (int i = 0; i < NO_OF_BUTTONS; i++) {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

        // Update to handle multiple buttons
        switch(i) {
            case 0:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
                break;
            case 1:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
                break;
            case 2:
                debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
                break;
            default:
                break;
        }

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i]; // Debouncing logic

            if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
                // Button is pressed; we start counting
                if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                    counterForButtonPress1s[i]++;
                    if (counterForButtonPress1s[i] == DURATION_FOR_AUTO_INCREASING) {
                        // Flag is turned on when 1 second has passed since the button was pressed
                        flagForButtonPress1s[i] = 1;
                        flagForButtonPressShort[i] = 0; // Reset short press flag
                        counterForLongPressInterval[i] = 0;
                    }
                } else {
                    // The button is pressed for less than 1 second
                	counterForLongPressInterval[i]++;
                	if (counterForLongPressInterval[i] >= 25) {
						flagForButtonPressShort[i] = 0;
						flagForButtonPress1s[i] = 1; // Reset long press flag
						counterForLongPressInterval[i] = 0;
                	}
                }
            }

            if (buttonBuffer[i] == BUTTON_IS_RELEASED && previousButtonBuffer[i] == BUTTON_IS_PRESSED) {
				// Button has just been released
				if (counterForButtonPress1s[i] > 0 && counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
					// It was a short press
					flagForButtonPressShort[i] = 1;
				}
				// Reset counters and flags on release
				counterForButtonPress1s[i] = 0;
				counterForLongPressInterval[i] = 0;
				flagForButtonPress1s[i] = 0;
			}

			// Store the current button state for the next iteration
			previousButtonBuffer[i] = buttonBuffer[i];
        }
    }
}

// Function to check if button is pressed shorter than 1s
unsigned char is_button_pressed_short(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPressShort[index] == 1) {
        flagForButtonPressShort[index] = 0; // Reset the flag
        return 1;
    }
    return 0;
}

// Function to check if button is pressed longer than 1s
unsigned char is_button_pressed_1s(uint8_t index) {
    if (index >= NO_OF_BUTTONS) return 0;
    if (flagForButtonPress1s[index] == 1) {
        flagForButtonPress1s[index] = 0; // Reset the flag
        return 1;
    }
    return 0;
}

