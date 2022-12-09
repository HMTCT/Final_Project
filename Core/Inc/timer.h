/*
 * timer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: HMT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_


extern int timer0_flag;
void setTimer0(int duration);


extern int timer1_flag;
void setTimer1(int duration);


extern int timer2_flag;
void setTimer2(int duration);


extern int timer3_flag;
void setTimer3(int duration);

extern int timer4_flag;
void setTimer4(int duration);

extern int timer5_flag;
void setTimer5(int duration);


void timer_run();



#endif /* INC_TIMER_H_ */
