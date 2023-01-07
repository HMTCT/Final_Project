/*
 * scheduler.h
 *
 *  Created on: Nov 11, 2022
 *      Author: HMT
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define TICK_CYCLE		10

#define FSM_AUTO1_ID	1
#define FSM_AUTO2_ID	2
#define FSM_BLINKING_ID	3
#define AUTO_AGAIN_ID	4
#define PEDES_LIGHT_ID	5
#define BUZZER_ID		6
#define FSM_7SEG_ID		7

typedef struct{
	void (*pTask)(void);
	uint32_t 	Delay;
	uint32_t 	Period;
	uint8_t 	RunMe;

	uint32_t 	TaskID;
}sTasks;

#define SCH_MAX_TASKS	40

void SCH_Init(void);

void SCH_Add_Task ( void (*pFunction)() ,
					uint32_t DELAY,
					uint32_t PERIOD,
					uint32_t taskID);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete_Task(uint32_t taskID);

void SCH_Delete_All();


#endif /* INC_SCHEDULER_H_ */
