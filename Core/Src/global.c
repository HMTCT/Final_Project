/*
 * global.c
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */


#include "global.h"

int status1 		= INIT;
int status2 		= INIT;
int MODE 			= INIT;

int RED_DURATION 	= 5000;
int YELLOW_DURATION	= 2000;
int GREEN_DURATION	= 3000;

int led_buffer[4] 	= {1, 2, 3, 4};

int countdown1 		= 0;
int countdown2 		= 0;
