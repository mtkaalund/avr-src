#include "timer1_ctc.h"

void timer1_ctc_init(void)
{

	TCCR1B |= (1 << WGM12); //Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A);	//Enable CTC interrupt
	sei();			//Enable global interrupt
}

void timer1_ctc_set(unsigned int foc1a)
{
/*
	N = { 1, 8, 64, 256, 1024 }
	f_clk = f_cpu
	Focna = f_clk / ( 2 * N * (1 + OCRnA ) )
=>	(1 + OCRnA) * Focna = f_clk / ( 2 * N )
=>	(1 + OCRnA) = f_clk / ( 2 * N * Focna )
=>	OCRnA = f_clk / ( 2 * N * Focna ) - 1

	OCRnA = 16000000 / ( 2 * 64 * 1000 ) - 1 = 
*/
	OCR1A = foc1a;// 15624;		//Count to
	TCCR1B |= (BIT(CS10) | BIT(CS12)); //Start timer at Fcpu/64
}
