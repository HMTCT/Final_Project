/*
 * traffic_light.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "traffic_light.h"

void traffic_light1(){
	HAL_GPIO_WritePin (GPIOA, RED_ROAD1_Pin| YELLOW_ROAD1_Pin| GREEN_ROAD1_Pin, 1);
	if (status1 == AUTO_GREEN){		//green turns on
		HAL_GPIO_WritePin (GREEN_ROAD1_GPIO_Port, GREEN_ROAD1_Pin,
		GPIO_PIN_RESET);
	}
	if (status1 == AUTO_YELLOW){		//yellow turns on
		HAL_GPIO_WritePin (YELLOW_ROAD1_GPIO_Port, YELLOW_ROAD1_Pin,
		GPIO_PIN_RESET );
	}
	if (status1 == AUTO_RED) {		//red turns on
		HAL_GPIO_WritePin (RED_ROAD1_GPIO_Port, RED_ROAD1_Pin,
		GPIO_PIN_RESET ) ;
	}
}

void traffic_light2(){
	HAL_GPIO_WritePin (GPIOA, RED_ROAD2_Pin| YELLOW_ROAD2_Pin| GREEN_ROAD2_Pin, 1) ;
	if (status2 == AUTO_GREEN){		//green turns on
		HAL_GPIO_WritePin (GREEN_ROAD2_GPIO_Port, GREEN_ROAD2_Pin,
		GPIO_PIN_RESET);
	}
	if (status2 == AUTO_YELLOW){	//yellow turns on
		HAL_GPIO_WritePin (YELLOW_ROAD2_GPIO_Port, YELLOW_ROAD2_Pin,
		GPIO_PIN_RESET );
	}
	if( status2 == AUTO_RED) {		//red turns on
		HAL_GPIO_WritePin (RED_ROAD2_GPIO_Port, RED_ROAD2_Pin,
		GPIO_PIN_RESET ) ;
	}
}

void fsm_automatic_run1(){
	switch (status1) {
		case INIT:
			status1 = AUTO_RED;
			setTimer1(10);
			break;
		case AUTO_RED:
			if (timer1_flag == 1){
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
			}
			break;
		case AUTO_YELLOW:
			if (timer1_flag == 1){
				traffic_light1();
				status1 = AUTO_RED;
				countdown1 = YELLOW_DURATION / 1000;
				setTimer1(YELLOW_DURATION);
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

void turn_off_all_lights(){
	HAL_GPIO_WritePin (GPIOA, RED_ROAD1_Pin| YELLOW_ROAD1_Pin| GREEN_ROAD1_Pin, 1);
	HAL_GPIO_WritePin (GPIOA, RED_ROAD2_Pin| YELLOW_ROAD2_Pin| GREEN_ROAD2_Pin, 1);
}

void fsm_blinking_mode(){
	if (timer4_flag == 1){
		switch (MODE) {
			case 2:
				HAL_GPIO_WritePin (GPIOA, YELLOW_ROAD1_Pin| GREEN_ROAD1_Pin, 1);
				HAL_GPIO_WritePin (GPIOA, YELLOW_ROAD2_Pin| GREEN_ROAD2_Pin, 1);
				HAL_GPIO_TogglePin(GPIOA, RED_ROAD1_Pin | RED_ROAD2_Pin);
				break;
			case 3:
				HAL_GPIO_WritePin (GPIOA, RED_ROAD1_Pin| GREEN_ROAD1_Pin, 1);
				HAL_GPIO_WritePin (GPIOA, RED_ROAD2_Pin| RED_ROAD2_Pin, 1);
				HAL_GPIO_TogglePin(GPIOA, YELLOW_ROAD1_Pin | YELLOW_ROAD2_Pin);
				break;
			case 4:
				HAL_GPIO_WritePin (GPIOA, YELLOW_ROAD1_Pin| RED_ROAD1_Pin, 1);
				HAL_GPIO_WritePin (GPIOA, YELLOW_ROAD2_Pin| RED_ROAD2_Pin, 1);
				HAL_GPIO_TogglePin(GPIOA, GREEN_ROAD1_Pin | GREEN_ROAD2_Pin);
				break;
			default:
				break;
		}
		setTimer4(250);
	}
}
