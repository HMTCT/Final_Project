/*
 * display7SEG.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#include "main.h"
#include "display7SEG.h"

#define MAX_LED		4

static int index_led = 0;

void display7SEG(int counter){
	HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|b_7SEG_Pin|c_7SEG_Pin|d_7SEG_Pin
		  			  		 |e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 0);
	switch (counter){
		case 0:
			HAL_GPIO_WritePin(GPIOB, g_7SEG_Pin, 1);
	  		break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|d_7SEG_Pin|e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
		case 2:
	  		HAL_GPIO_WritePin(GPIOB, c_7SEG_Pin|f_7SEG_Pin, 1);
	  		break;
	  	  case 3:
	  		HAL_GPIO_WritePin(GPIOB, e_7SEG_Pin|f_7SEG_Pin, 1);
	  		break;
	  	  case 4:
	  		HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|d_7SEG_Pin|e_7SEG_Pin, 1);
	  		break;
	  	  case 5:
	  		HAL_GPIO_WritePin(GPIOB, b_7SEG_Pin|e_7SEG_Pin, 1);
	  		break;
	  	  case 6:
	  		HAL_GPIO_WritePin(GPIOB, b_7SEG_Pin, 1);
	  		break;
	  	  case 7:
	  		HAL_GPIO_WritePin(GPIOB, d_7SEG_Pin|e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
	  	  case 8:
	  		break;
	  	  case 9:
	  		HAL_GPIO_WritePin(GPIOB, e_7SEG_Pin, 1);
	  		break;
	  	  default:
	  		HAL_GPIO_WritePin(GPIOB, a_7SEG_Pin|b_7SEG_Pin|c_7SEG_Pin|d_7SEG_Pin
	  			  		             |e_7SEG_Pin|f_7SEG_Pin|g_7SEG_Pin, 1);
	  		break;
	  }
}

void update7SEG(int index){
	HAL_GPIO_WritePin(GPIOA, EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin, 1);
	display7SEG(led_buffer[index]);
    switch (index){
        case 0:
            //Display the first 7SEG with led_buffer[0]
        	HAL_GPIO_WritePin(GPIOA, EN0_Pin, 0);
            break;
        case 1:
            //Display the second 7SEG with led_buffer[1]
        	HAL_GPIO_WritePin(GPIOA, EN1_Pin, 0);
            break;
        case 2:
            //Display the third 7SEG with led_buffer[2]
        	HAL_GPIO_WritePin(GPIOA, EN2_Pin, 0);
            break;
        case 3:
            //Display the forth 7SEG with led_buffer[3]
        	HAL_GPIO_WritePin(GPIOA, EN3_Pin, 0);
            break;
        default:
            break;
    }
}

void fsm_for_7SEG(){
	switch (MODE) {
		case INIT:
			update_led_buffer(INIT);
			MODE = 1;
			setTimer0(10);
			break;
		case 1:
			if (timer0_flag == 1){
				update_led_buffer(1);
				if (index_led >= MAX_LED) index_led = 0;
				update7SEG(index_led++);
				setTimer0(250);
			}
			break;
		 default:
			if (timer0_flag == 1){
				update_led_buffer(MODE);
				if (index_led >= MAX_LED) index_led = 0;
				update7SEG(index_led++);
				setTimer0(250);
			}
			break;
	}
}

void update_led_buffer(int mode){
	switch (MODE) {
		case INIT:
			setTimer3(10);
			MODE = 1;
			break;
		case 1:
			if (timer3_flag == 1){
				countdown1--;
				countdown2--;

				if (countdown1 < 0) countdown1 = 0;
				if (countdown2 < 0) countdown2 = 0;

				led_buffer[0] = countdown1 / 10;
				led_buffer[1] = countdown1 % 10;
				led_buffer[2] = countdown2 % 10;
				led_buffer[3] = countdown2 / 10;

				setTimer3(1000);
			}
			break;
		case 2:
			led_buffer[0] = 0;
			led_buffer[1] = MODE;
			led_buffer[2] = (RED_DURATION / 1000) % 10;
			led_buffer[3] = RED_DURATION / 10000;
			break;
		case 3:
			led_buffer[0] = 0;
			led_buffer[1] = MODE;
			led_buffer[2] = (YELLOW_DURATION / 1000) % 10;
			led_buffer[3] = YELLOW_DURATION / 10000;
			break;
		case 4:
			led_buffer[0] = 0;
			led_buffer[1] = MODE;
			led_buffer[2] = (GREEN_DURATION / 1000) % 10;
			led_buffer[3] = GREEN_DURATION / 10000;
			break;
		default:
			break;
	}
}
