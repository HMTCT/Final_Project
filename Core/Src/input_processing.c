/*
 * input_processing.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "input_processing.h"
#include "traffic_light.h"
#include "scheduler.h"
#include "global.h"

#define NO_OF_BUTTONS	4

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
					if (i == A1_IS_PRESSED && MODE > 1)
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
					if (i == A2_IS_PRESSED && timer5_flag == 1 && !MANUAL_MODE){
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
		//A1 is pressed
		case A1_IS_PRESSED:
			MODE = (MODE + 1) % 5;
			RED_DURATION = OLD_RED_DURATION;
			YELLOW_DURATION = OLD_YELLOW_DURATION;
			GREEN_DURATION = OLD_GREEN_DURATION;
			MANUAL_MODE = 0;

			if (MODE == INIT){
				//MODE = INIT;
				validate_traffic_light();
				status1 = INIT;
				status2 = INIT;
			}
			else{
				status1 = STOP;
				status2 = STOP;

				//Turn off all leds before blinking
				HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0); //TURN OFF
				HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0); //TURN OFF

				HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0); //TURN OFF
				HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0); //TURN OFF
			}

			if (USE_SCHEDULER){
				if (MODE == INIT){
					SCH_Delete_Task(FSM_BLINKING_ID);
					SCH_Add_Task(fsm_automatic_run1, 0, 0, FSM_AUTO1_ID);
					SCH_Add_Task(fsm_automatic_run2, 1, 0, FSM_AUTO2_ID);
					return;
				}
				if (MODE == TUNING_RED){
					SCH_Delete_Task(FSM_AUTO1_ID);
					SCH_Delete_Task(FSM_AUTO2_ID);
					SCH_Add_Task(fsm_blinking_mode, 1, 25, FSM_BLINKING_ID);
				}
			}
			break;
		//A2 is pressed
		case A2_IS_PRESSED:
			switch (MODE) {
				case AUTOMATIC:
					MANUAL_MODE = 1;
					setTimer7(TIMEOUT_MANUAL);

					if (USE_SCHEDULER){
						SCH_Delete_Task(FSM_AUTO1_ID);
						SCH_Delete_Task(FSM_AUTO2_ID);
						SCH_Delete_Task(AUTO_AGAIN_ID);
						SCH_Add_Task(automatic_after_manual, TIMEOUT_MANUAL / TICK_CYCLE, 0, AUTO_AGAIN_ID);
					}

					switch (status1) {
						case AUTO_RED:
							status1 = AUTO_GREEN;
							break;
						case AUTO_YELLOW:
							status1 = AUTO_RED;
							break;
						case AUTO_GREEN:
							status1 = AUTO_YELLOW;
						default:
							break;
					}
					traffic_light1();
					break;
				case TUNING_RED:
					RED_DURATION = (RED_DURATION + 1000) % 99000;
					break;
				case TUNING_YELLOW:
					YELLOW_DURATION = (YELLOW_DURATION + 1000) % 99000;
					break;
				case TUNING_GREEN:
					GREEN_DURATION = (GREEN_DURATION + 1000) % 99000;
					break;
				default:
					break;
			}
			break;
		//A3 is pressed
		case A3_IS_PRESSED:
			switch (MODE) {
				case AUTOMATIC:
					MANUAL_MODE = 1;
					setTimer7(TIMEOUT_MANUAL);

					if (USE_SCHEDULER){
						SCH_Delete_Task(FSM_AUTO1_ID);
						SCH_Delete_Task(FSM_AUTO2_ID);
						SCH_Delete_Task(AUTO_AGAIN_ID);
						SCH_Add_Task(automatic_after_manual, TIMEOUT_MANUAL / TICK_CYCLE, 0, AUTO_AGAIN_ID);
					}

					switch (status2) {
						case AUTO_RED:
							status2 = AUTO_GREEN;
							break;
						case AUTO_YELLOW:
							status2 = AUTO_RED;
							break;
						case AUTO_GREEN:
							status2 = AUTO_YELLOW;
							break;
						default:
							break;
					}
					traffic_light2();
					break;
				case TUNING_RED:
					OLD_RED_DURATION = RED_DURATION;
					break;
				case TUNING_YELLOW:
					OLD_YELLOW_DURATION = YELLOW_DURATION;
					break;
				case TUNING_GREEN:
					OLD_GREEN_DURATION = GREEN_DURATION;
				default:
					break;
			}
			break;
		//A0 is pressed
		case A0_IS_PRESSED:
			//HAL_GPIO_TogglePin(D6_GPIO_Port, D6_Pin);
			//HAL_GPIO_TogglePin(D7_GPIO_Port, D7_Pin);
			pedes_en = 1;
			buzzer = 1;
			setTimer6(2 * (RED_DURATION + YELLOW_DURATION + GREEN_DURATION));	//Set timeout for pedestrian light and buzzer
			if (USE_SCHEDULER){
				SCH_Delete_Task(PEDES_LIGHT_ID);
				SCH_Delete_Task(BUZZER_ID);
				SCH_Add_Task(pedestrian_light, 1, 0, PEDES_LIGHT_ID);
				SCH_Add_Task(buzzer_active, 1, 0, BUZZER_ID);
			}
			break;
		default:
			break;
	}
}
