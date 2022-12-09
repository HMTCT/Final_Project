/*
 * display7SEG.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "timer.h"
#include "global.h"
#include "traffic_light.h"


void display7SEG(int counter);
void update7SEG(int index);
void fsm_for_7SEG();
void update_led_buffer(int);

#endif /* INC_DISPLAY7SEG_H_ */
