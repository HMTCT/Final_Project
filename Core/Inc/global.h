/*
 * global.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_


#define INIT 			0
#define AUTO_RED 		1
#define AUTO_GREEN 		2
#define AUTO_YELLOW 	3

#define AUTOMATIC		1
#define TUNING_RED		2
#define TUNING_YELLOW	3
#define TUNING_GREEN	4

#define AUTO_INC		10
#define AUTO_DEC		11
#define STOP			12

#define A0_IS_PRESSED	0
#define A1_IS_PRESSED	1
#define A2_IS_PRESSED	2
#define A3_IS_PRESSED	3

#define TIMEOUT_MANUAL	3000

extern int status1;
extern int status2;

extern int RED_DURATION;
extern int YELLOW_DURATION;
extern int GREEN_DURATION;

extern int MODE;
extern int MANUAL_MODE;

extern int led_buffer[4];

extern int countdown1;
extern int countdown2;

extern int pedes_Duration;

extern int buzzer;

extern int pedes_en;

extern int USE_SCHEDULER;
extern int auto1_period;
extern int auto2_period;

#endif /* INC_GLOBAL_H_ */
