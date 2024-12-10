/*
 * fsm_setting.c
 *
 *  Created on: Oct 24, 2024
 *      Author: phuct
 */

#include "fsm_setting.h"

void fsm_setting_run(){
	switch(status){
	case SET_MODE1:
		setTrafficRed1();
		setTrafficRed2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeRed--;
		}
		else if(is_button_pressed_1s(0) == 1){
			defaultTimeRed--;
		}
		else if(is_button_pressed_short(2) == 1){
			defaultTimeRed++;
		}
		else if(is_button_pressed_1s(2) == 1){
			defaultTimeRed++;
		}
		if(defaultTimeRed < 0){
			defaultTimeRed = 99;
		}
		if(defaultTimeRed > 99){
			defaultTimeRed = 0;
		}
		sprintf(buffer1, "Mode: REDMODE");
		sprintf(buffer2, "RED: %.2f", (float)defaultTimeRed);
		if(is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = SET_MODE2;
			sprintf(buffer1, "Mode: YELLOWMODE");
			sprintf(buffer2, "YELLOW: %.2f", (float)defaultTimeYellow);
		}
		if(is_button_pressed_1s(1) == 1){
			setTimer1(250);
			status = AUTO_RED_GREEN;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		break;
	case SET_MODE2:
		setTrafficYellow1();
		setTrafficYellow2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeYellow--;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeYellow--;
		}
		if(is_button_pressed_short(2) == 1){
			defaultTimeYellow++;
		}
		if(is_button_pressed_1s(2) == 1){
			defaultTimeYellow++;
		}
		if(defaultTimeYellow < 0){
			defaultTimeYellow = 99;
		}
		if(defaultTimeYellow > 99){
			defaultTimeYellow = 0;
		}
		sprintf(buffer1, "Mode: YELLOWMODE");
		sprintf(buffer2, "YELLOW: %.2f", (float)defaultTimeYellow);
		if(is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = SET_MODE3;
			sprintf(buffer1, "Mode: GREENMODE");
			sprintf(buffer2, "GREEN: %.2f", (float)defaultTimeGreen);
		}
		if(is_button_pressed_1s(1) == 1){
			setTimer1(250);
			status = AUTO_RED_GREEN;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		break;
	case SET_MODE3:
//		updateClockBuffer(3, defaultTimeGreen);
		setTrafficGreen1();
		setTrafficGreen2();
		if(is_button_pressed_short(0) == 1){
			defaultTimeGreen--;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeGreen--;
		}
		if(is_button_pressed_short(2) == 1){
			defaultTimeGreen++;
		}
		if(is_button_pressed_1s(0) == 1){
			defaultTimeGreen++;
		}
		if(defaultTimeGreen < 0){
			defaultTimeGreen = 99;
		}
		if(defaultTimeGreen > 99){
			defaultTimeGreen = 0;
		}
		sprintf(buffer1, "Mode: GREENMODE");
		sprintf(buffer2, "GREEN: %.2f", (float)defaultTimeGreen);
		if(is_button_pressed_1s(1) == 1 || is_button_pressed_short(1) == 1){
			setTimer1(250);
			status = AUTO_RED_GREEN;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN);
		}
		break;
	default:
		break;
	}
}
