/*
 * timer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_


//Timer for FSM 7SEG
extern int timer0_flag;
void setTimer0(int duration);

//Timer for FSM automatic 1
extern int timer1_flag;
void setTimer1(int duration);

//Timer for FSM automatic 2
extern int timer2_flag;
void setTimer2(int duration);

//Timer for update led buffer
extern int timer3_flag;
void setTimer3(int duration);

//Timer for blinking mode
extern int timer4_flag;
void setTimer4(int duration);

//Timer for auto increasing mode
extern int timer5_flag;
void setTimer5(int duration);

//Timer for pedestrian
extern int timer6_flag;
void setTimer6(int duration);


void timer_run();



#endif /* INC_TIMER_H_ */
