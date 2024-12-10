/*
 * fsm_manual.c
 *
 *  Created on: Oct 22, 2024
 *      Author: phuct
 */

#include "fsm_manual.h"

void fsm_manual_run(){
	switch(status){
	case MAN_MODE1:
		//Return to status INIT / AUTO_RED_GREEN
		setTimer1(defaultTimeGreen*1000);
		setTimer2(1000);
		timeRED = defaultTimeRed;
		timeGREEN = defaultTimeGreen;
		tmpYELLOW = defaultTimeYellow;
		sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
		sprintf(buffer2, "Line2: %.2f", (float)timeGREEN--);
		status = AUTO_RED_GREEN;
		break;
	case MAN_MODE2:
		//Counter for returning to automatic mode after 5 second
		if(timer4_flag == 1){
			status = MAN_MODE1;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		if(blink_status == 0){
			setTrafficRed1();
			setTrafficRed2();
		} else {
			setTrafficOff();
		}
		//If BUTTON1 is pressed, switch to status MAN_MODE3
		if(is_button_pressed_short(0) == 1){
			status = MAN_MODE3;
			setTimer1(500); //2Hz mean 2 LEDs turn ON for 1 sec, each LED ON for 500ms
			setTimer4(5000);
			blink_status = 0;
			sprintf(buffer1, "Mode: Yellow ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpYELLOW);
		}
		else if(is_button_pressed_1s(0) == 1){
			status = MAN_MODE3;
			setTimer1(500);
			setTimer4(5000);
			blink_status = 0;
			sprintf(buffer1, "Mode: Yellow ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpYELLOW);
		}
		//Blinking Red LEDs
		if(timer1_flag == 1){
			setTimer1(500);
			blink_status = 1 - blink_status;
		}
		//If BUTTON2 is pressed, tempRED value increase 1 unit
		//If value overcome 99, it return to 1
		if(is_button_pressed_short(1) == 1){
			setTimer4(5000);
			tmpRED++;
			if(tmpRED > 99) tmpRED = 1;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		else if(is_button_pressed_1s(1) == 1){
			setTimer4(5000);
			tmpRED++;
			if(tmpRED > 99) tmpRED = 1;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		//If BUTTON3 is pressed, tmpRED is assigned for defaultTimeRed
		if(is_button_pressed_short(2) == 1){
			setTimer4(5000);
			defaultTimeRed = tmpRED;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)defaultTimeRed);
		}
 // MAN 2 display the current Mode 2 to blink Red LEDs
		break;
	case MAN_MODE3:
		//Counter for returning to automatic mode after 5 second
		if(timer4_flag == 1){
			status = MAN_MODE1;
		}
		if(blink_status == 0){
			setTrafficYellow1();
			setTrafficYellow2();
		} else {
			setTrafficOff();
		}
		//If BUTTON1 is pressed, switch to status MAN_MODE4
		if(is_button_pressed_short(0) == 1){
			setTimer4(5000);
			status = MAN_MODE4;
			setTimer1(500);
			blink_status = 0;
			sprintf(buffer1, "Mode: Green ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpGREEN);
		}
		else if(is_button_pressed_1s(0) == 1){
			setTimer4(5000);
			status = MAN_MODE4;
			setTimer1(500);
			blink_status = 0;
			sprintf(buffer1, "Mode: Green ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpGREEN);
		}
		if(timer1_flag == 1){
			setTimer1(500);
			blink_status = 1 - blink_status;
		}

		if(is_button_pressed_short(1) == 1){
			setTimer4(5000);
			tmpYELLOW++;
			if(tmpYELLOW > 99) tmpYELLOW = 1;
			sprintf(buffer1, "Mode: Yellow ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpYELLOW);
		}
		else if(is_button_pressed_1s(1) == 1){
			setTimer4(5000);
			tmpYELLOW++;
			if(tmpYELLOW > 99) tmpYELLOW = 1;
			sprintf(buffer1, "Mode: Yellow ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpYELLOW);

		}
		if(is_button_pressed_short(2) == 1){
			setTimer4(5000);
			defaultTimeYellow = tmpYELLOW;
			sprintf(buffer1, "Mode: Yellow ");
			sprintf(buffer2, "Duration: %.2f", (float)defaultTimeYellow);
		}
	//MAN 3 display the current Mode 3 to blink Amber LEDs
		break;
	case MAN_MODE4:
		//Counter for returning to automatic mode after 5 second
		if(timer4_flag == 1){
			status = MAN_MODE1;
		}
		//If BUTTON1 is pressed, switch to status MAN_MODE1
		if(is_button_pressed_short(0) == 1){
			setTimer4(5000);
			status = MAN_MODE1;
			if((defaultTimeRed - (defaultTimeGreen + defaultTimeYellow)) < 0){
				if(defaultTimeRed < (defaultTimeGreen + defaultTimeYellow)){
					defaultTimeYellow = preTimeYellow;
					defaultTimeGreen = preTimeGreen;
					defaultTimeRed = preTimeRed;
					tmpYELLOW = preTimeYellow;
					tmpGREEN = preTimeGreen;
					tmpRED = preTimeRed;
				} else {
					preTimeYellow = defaultTimeYellow ;
					preTimeGreen = defaultTimeGreen;
					preTimeRed = defaultTimeRed;
					tmpYELLOW = preTimeYellow;
					tmpGREEN = preTimeGreen;
					tmpRED = preTimeRed;
				}
			}
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		else if(is_button_pressed_1s(0) == 1){
			setTimer4(5000);
			status = MAN_MODE1;
			if((defaultTimeRed - (defaultTimeGreen + defaultTimeYellow)) < 0){
				if(defaultTimeRed < (defaultTimeGreen + defaultTimeYellow)){
					defaultTimeYellow = preTimeYellow;
					defaultTimeGreen = preTimeGreen;
					defaultTimeRed = preTimeRed;
					tmpYELLOW = preTimeYellow;
					tmpGREEN = preTimeGreen;
					tmpRED = preTimeRed;
				} else {
					preTimeYellow = defaultTimeYellow ;
					preTimeGreen = defaultTimeGreen;
					preTimeRed = defaultTimeRed;
					tmpYELLOW = preTimeYellow;
					tmpGREEN = preTimeGreen;
					tmpRED = preTimeRed;
				}
			}
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		//Only Green LEDs in both Road 1 and 2 are ON, other LEDs are OFF
		if(blink_status == 0){
			setTrafficGreen1();
			setTrafficGreen2();
		} else {
			setTrafficOff();
		}
		//Blinking Green LEDs
		if(timer1_flag == 1){
			blink_status = 1 - blink_status;
			setTimer1(500);
		}
		//If BUTTON2 is pressed, tmpGREEN value increase 1 unit
		//If value overcome 99, it return to 1
			if(is_button_pressed_short(1) == 1){
				setTimer4(5000);
				tmpGREEN++;
				if(tmpGREEN > 99) tmpGREEN = 1;
				sprintf(buffer1, "Mode: Green ");
				sprintf(buffer2, "Duration: %.2f", (float)tmpGREEN);
			}
			if(is_button_pressed_1s(1) == 1){
				setTimer4(5000);
				tmpGREEN++;
				if(tmpGREEN > 99) tmpGREEN = 1;
				sprintf(buffer1, "Mode: Green ");
				sprintf(buffer2, "Duration: %.2f", (float)tmpGREEN);
			}
		//If BUTTON3 is pressed, tmpGREEN is assigned for defaultTimeGreen
			if(is_button_pressed_short(2) == 1){
				setTimer4(5000);
				defaultTimeGreen = tmpGREEN;
				sprintf(buffer1, "Mode: Green ");
				sprintf(buffer2, "Duration: %.2f", (float)defaultTimeGreen);
			}
	//Num 4 display the current Mode 4 to blink Green LEDs
		break;
	default:
		break;
	}
}
