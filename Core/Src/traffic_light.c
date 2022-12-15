/*
 * traffic_light.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "traffic_light.h"

void traffic_light1(){
	if (status1 == AUTO_GREEN){		//green turns on
		HAL_GPIO_WritePin (D2_GPIO_Port, D2_Pin, 0);
		HAL_GPIO_WritePin (D3_GPIO_Port, D3_Pin, 1);
	}
	if (status1 == AUTO_YELLOW){		//yellow turns on
		HAL_GPIO_WritePin (D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin (D3_GPIO_Port, D3_Pin, 1);
	}
	if (status1 == AUTO_RED) {		//red turns on
		HAL_GPIO_WritePin (D2_GPIO_Port, D2_Pin, 1);
		HAL_GPIO_WritePin (D3_GPIO_Port, D3_Pin, 0);
	}
}

void traffic_light2(){
	if (status2 == AUTO_GREEN){		//green turns on
		HAL_GPIO_WritePin (D4_GPIO_Port, D4_Pin, 0);
		HAL_GPIO_WritePin (D5_GPIO_Port, D5_Pin, 1);
	}
	if (status2 == AUTO_YELLOW){	//yellow turns on
		HAL_GPIO_WritePin (D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin (D5_GPIO_Port, D5_Pin, 1);
	}
	if( status2 == AUTO_RED) {		//red turns on
		HAL_GPIO_WritePin (D4_GPIO_Port, D4_Pin, 1);
		HAL_GPIO_WritePin (D5_GPIO_Port, D5_Pin, 0);
	}
}


void pedestrian_light(){
	if (!pedes_en || timer6_flag == 1){
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
		HAL_GPIO_WritePin (D7_GPIO_Port, D7_Pin, 0);
		pedes_en = 0;
		buzzer = 0;
		duty = 0;
		return;

	}

	switch (status1) {
		case AUTO_GREEN:
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 0);
			HAL_GPIO_WritePin (D7_GPIO_Port, D7_Pin, 1);
			buzzer = 1;
			break;
		case AUTO_YELLOW:
			HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, 1);
			HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, 0);
			buzzer = 0;
			duty = 0;
			break;
		case AUTO_RED:
			HAL_GPIO_WritePin (D6_GPIO_Port, D6_Pin, 1);
			HAL_GPIO_WritePin (D7_GPIO_Port, D7_Pin, 0);
			buzzer = 0;
			duty = 0;
			break;
		default:
			break;
	}
}


void fsm_automatic_run1(){
	switch (status1) {
		case INIT:
			status1 = AUTO_RED;
			setTimer1(10);
			setTimer3(10);
			MODE = 1;
			break;
		case AUTO_RED:
			if (timer1_flag == 1){
				buzzer = 1;
				traffic_light1();
				status1 = AUTO_GREEN;
				countdown1 = RED_DURATION / 1000;
				setTimer1(RED_DURATION);
			}
			break;
		case AUTO_GREEN:
			if (timer1_flag == 1){
				traffic_light1();
				status1 = AUTO_YELLOW;
				countdown1 = GREEN_DURATION / 1000;
				setTimer1(GREEN_DURATION);
				buzzer = 0;
			}
			break;
		case AUTO_YELLOW:
			if (timer1_flag == 1){
				traffic_light1();
				status1 = AUTO_RED;
				countdown1 = YELLOW_DURATION / 1000;
				setTimer1(YELLOW_DURATION);
				buzzer = 0;
			}
			break;
		case STOP:
			break;
		default:
			break;
	}
}

void fsm_automatic_run2(){
	switch (status2) {
		case INIT:
			status2 = AUTO_GREEN;
			setTimer2(10);
			break;
		case AUTO_RED:
			if (timer2_flag == 1){
				traffic_light2();
				status2 = AUTO_GREEN;
				countdown2 = RED_DURATION / 1000;
				setTimer2(RED_DURATION);
			}
			break;
		case AUTO_GREEN:
			if (timer2_flag == 1){
				traffic_light2();
				status2 = AUTO_YELLOW;
				countdown2 = GREEN_DURATION / 1000;
				setTimer2(GREEN_DURATION);
			}
			break;
		case AUTO_YELLOW:
			if (timer2_flag == 1){
				traffic_light2();
				status2 = AUTO_RED;
				countdown2 =  YELLOW_DURATION / 1000;
				setTimer2(YELLOW_DURATION);
			}
			break;
		case STOP:
			break;
		default:
			break;
	}
}

/*
void turn_off_all_lights(){
	HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, 0); //TURN OFF
	HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, 0); //TURN OFF

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, 0); //TURN OFF
	HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, 0); //TURN OFF
}
*/

void fsm_blinking_mode(){
	if (timer4_flag == 1){
		switch (MODE) {
			case 2:
				//Blinking Red Leds
				HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				break;
			case 3:
				//Blinking Amber Leds
				HAL_GPIO_TogglePin(D2_GPIO_Port, D2_Pin);
				HAL_GPIO_TogglePin(D4_GPIO_Port, D4_Pin);
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				break;
			case 4:
				//Blinking Green Leds
				HAL_GPIO_TogglePin(D3_GPIO_Port, D3_Pin);
				HAL_GPIO_TogglePin(D5_GPIO_Port, D5_Pin);
				break;
			default:
				break;
		}
		setTimer4(250);
	}
}

