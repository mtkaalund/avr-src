#ifndef _TIMER1_CTC_H
#define _TIMER1_CTC_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <bits.h>

/*
 Defines our prescale as a enum, just so the code is more readable
*/
typedef enum {
	STOP,
	CLK1,
	CLK8,
	CLK64,
	CLK256,
	CLK1024
} timer1_prescale;

void timer1_ctc_init(void);
void timer1_ctc_set(unsigned int foc1a);

#endif
