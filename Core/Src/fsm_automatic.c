/*
 * fsm_automatic.c
 *
 *  Created on: Oct 22, 2024
 *      Author: phuct
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch(status){
	case INIT:
		setTrafficOff();
		status = AUTO_RED_GREEN;
		setTimer1(defaultTimeGreen*1000); //Multiply by 1000 as we input with unit second
		timeRED = defaultTimeRed;
		timeGREEN = defaultTimeGreen;
		tmpRED = defaultTimeRed;
		tmpYELLOW = defaultTimeYellow;
		tmpGREEN = defaultTimeGreen;
		setTimer2(1000);
		sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
		sprintf(buffer2, "line2: %.2f", (float)timeGREEN--);
		break;
	case AUTO_RED_GREEN:
		setTrafficRed1();
		setTrafficGreen2();
		if(timer1_flag == 1){
			status = AUTO_RED_YELLOW;
			setTimer1(defaultTimeYellow*1000);
			timeYELLOW = defaultTimeYellow;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Line2: %.2f", (float)timeYELLOW--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
			sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(500);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: REDMODE");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_RED_YELLOW:
		setTrafficRed1();
		setTrafficYellow2();
		if(timer1_flag == 1){
			status = AUTO_GREEN_RED;
			setTimer1(defaultTimeGreen*1000);
			timeGREEN = defaultTimeGreen;
			timeRED = defaultTimeRed;
			sprintf(buffer1, "Line1: %.2f", (float)timeGREEN--);
			sprintf(buffer2, "Line2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
			sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Line2: %.2f", (float)timeYELLOW--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: REDMODE");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_GREEN_RED:
		setTrafficGreen1();
		setTrafficRed2();
		if(timer1_flag == 1){
			status = AUTO_YELLOW_RED;
			setTimer1(defaultTimeYellow*1000);
			timeYELLOW = defaultTimeYellow;
			sprintf(buffer1, "Line1: %.2f", (float)timeYELLOW--);
			sprintf(buffer2, "Line2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){
			sprintf(buffer1, "Line1: %.2f", (float)timeGREEN--);
			sprintf(buffer2, "Line2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		else if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: REDMODE");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		break;
	case AUTO_YELLOW_RED:
		setTrafficYellow1();
		setTrafficRed2();
		if(timer1_flag == 1){
			status = AUTO_RED_GREEN;
			setTimer1(defaultTimeGreen*1000);
			timeRED = defaultTimeRed;
			timeGREEN = defaultTimeGreen;
			sprintf(buffer1, "Line1: %.2f", (float)timeRED--);
			sprintf(buffer2, "Line2: %.2f", (float)timeGREEN--);
			setTimer2(1000);
		}
		if(timer2_flag == 1){

			sprintf(buffer1, "Line1: %.2f", (float)timeYELLOW--);
			sprintf(buffer2, "Line2: %.2f", (float)timeRED--);
			setTimer2(1000);
		}
		if(is_button_pressed_short(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			setTimer4(5000);
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_1s(0) == 1){
			setTimer1(250);
			status = MAN_MODE2;
			sprintf(buffer1, "Mode: Red ");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		if(is_button_pressed_short(1) == 1){
			setTimer1(1000);
			status = SET_MODE1;
			sprintf(buffer1, "Mode: REDMODE");
			sprintf(buffer2, "Duration: %.2f", (float)tmpRED);
		}
		break;
	default:
		break;
	}
}
