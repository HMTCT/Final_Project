/*
 * input_processing.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

#include "input_reading.h"
#include "traffic_light.h"
#include "global.h"

void fsm_for_input_processing(void);
void update_processing(int BUTTON);

#endif /* INC_INPUT_PROCESSING_H_ */
