/*
 * input_processing.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "input_processing.h"

#define NO_OF_BUTTONS	3

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND} ;
enum ButtonState buttonState[NO_OF_BUTTONS] = {BUTTON_RELEASED};

int OLD_RED_DURATION	= 5000;
int OLD_YELLOW_DURATION	= 2000;
int OLD_GREEN_DURATION	= 3000;


void fsm_for_input_processing(void){
	for (int i = 0; i < NO_OF_BUTTONS; ++i){
		switch(buttonState[i]){
			case BUTTON_RELEASED:
				if(is_button_pressed(i)){
					buttonState[i] = BUTTON_PRESSED;
					update_processing(i);
					if (i == 0 && MODE > 1)
						setTimer4(10);
				}
				break;
			case BUTTON_PRESSED:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;
				}
				else {
					if(is_button_pressed_1s(i)){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
						setTimer5(10);
					}
				}
				break;
			case BUTTON_PRESSED_MORE_THAN_1_SECOND:
				if(!is_button_pressed(i)){
					buttonState[i] = BUTTON_RELEASED;
				}

				else{
					//TODO
					if (i != 0 && timer5_flag == 1){
						update_processing(i);
						setTimer5(1000);
					}
				}
				break;
			default:
				break;
			}
	}
}

void update_processing(int BUTTON){
	switch (BUTTON) {
		case 0:
			MODE = (MODE + 1) % 5;
			RED_DURATION = OLD_RED_DURATION;
			YELLOW_DURATION = OLD_YELLOW_DURATION;
			GREEN_DURATION = OLD_GREEN_DURATION;

			if (MODE == INIT){
				//MODE = INIT;
				status1 = INIT;
				status2 = INIT;
			}
			else{
				status1 = STOP;
				status2 = STOP;
			}
			break;
		case 1:
			switch (MODE) {
				case 2:
					RED_DURATION = (RED_DURATION + 1000) % 99000;
					break;
				case 3:
					YELLOW_DURATION = (YELLOW_DURATION + 1000) % 99000;
					break;
				case 4:
					GREEN_DURATION = (GREEN_DURATION + 1000) % 99000;
					break;
				default:
					break;
			}
			break;
		case 2:
			switch (MODE) {
				case 2:
					OLD_RED_DURATION = RED_DURATION;
					break;
				case 3:
					OLD_YELLOW_DURATION = YELLOW_DURATION;
					break;
				case 4:
					OLD_GREEN_DURATION = GREEN_DURATION;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
