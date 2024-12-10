/*
 * buffer_update.c
 *
 *  Created on: Nov 8, 2024
 *      Author: phuct
 */


#include "buffer_update.h"

void buffer_update(){
	if(status == 1||2||3||4||5||10){
			if(is_button_pressed_short(2) == 1){
				if(tmpRED != defaultTimeRed) tmpRED = defaultTimeRed;
				if(tmpYELLOW != defaultTimeYellow) tmpYELLOW = defaultTimeYellow;
				if(tmpGREEN != defaultTimeGreen) tmpRED = defaultTimeGreen;
			}
			if(is_button_pressed_1s(2) == 1){
				if((defaultTimeRed - (defaultTimeGreen + defaultTimeYellow)) != 0){
					if((defaultTimeRed - (defaultTimeGreen + defaultTimeYellow)) > 0){
						defaultTimeYellow++;
						defaultTimeGreen = defaultTimeRed - defaultTimeYellow;
					}
					if((defaultTimeRed - (defaultTimeGreen + defaultTimeYellow)) < 0){
						if(defaultTimeRed < (defaultTimeGreen + defaultTimeYellow)){
							defaultTimeYellow = 2;
							defaultTimeGreen = 3;
							defaultTimeRed = 5;
						}
					}
				}
			}
	}
}
