#ifndef _TIMER1_CTC_H
#define _TIMER1_CTC_H

#include <avr/io.h>
#include <bits.h>

void timer1_ctc_init(void);
void timer1_ctc_set(unsigned int foc1a);

#endif
