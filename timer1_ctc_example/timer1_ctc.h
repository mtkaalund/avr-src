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
	CLK1024,
	EXT_FALL,
	EXT_RISE
} Timer1Prescale;

void timer1_ctc_init(void);
void timer1_ctc_set_value( uint16_t ocr1a_value );
void timer1_ctc_set_prescale( Timer1Prescale pre);
#endif
