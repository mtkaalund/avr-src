#include "timer1_ctc.h"

void timer1_ctc_init(void)
{

	TCCR1B |= (1 << WGM12); //Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A);	//Enable CTC interrupt
}

void timer1_ctc_set_value( uint16_t ocr1a_value )
{
/*
	OCRnA = 16000000 / ( 2 * 64 * 1000 ) - 1 = 
*/

	cli();		//Disable interrupts
	OCR1A = ocr1a_value;
	sei();		//Enable interrupts
}

void timer1_ctc_set_prescale( Timer1Prescale pre)
{
	cli();		// Disable interrupts

	switch(pre)
	{
	case STOP:
		/* unset CS12 CS11 CS10 */
		bit_clear(TCCR1B, BIT(CS12) | BIT(CS11) | BIT(CS10));
		break;
	case CLK1:
		/* unset CS12 CS11 set CS10 */
		bit_clear(TCCR1B, BIT(CS12) | BIT(CS11));
		bit_set(TCCR1B, BIT(CS10));
		break;
	case CLK8:
		/* unset CS12 CS10 set CS11 */
		bit_clear(TCCR1B, BIT(CS12) | BIT(CS10));
		bit_set(TCCR1B, BIT(CS11));
		break;
	case CLK64:
		/* unset CS12 set CS11 CS10 */ 
		bit_clear(TCCR1B, BIT(CS12));
		bit_set(TCCR1B, BIT(CS11) | BIT(CS10));
//		TCCR1B |= (BIT(CS10) | BIT(CS12)); //Start timer at Fcpu/64
		break;
	case CLK256:
		/* unset CS11 CS10 set CS12 */
		bit_clear(TCCR1B, BIT(CS11) | BIT(CS10));
		bit_set(TCCR1B, BIT(CS12));
		break;
	case CLK1024:
		/* unset CS11 set CS12 CS10 */
		bit_clear(TCCR1B, BIT(CS11));
		bit_set(TCCR1B, BIT(CS12) | BIT(CS10));
		break;
	case EXT_FALL:
		/* unset CS10 set CS12 CS11 */
		bit_clear(TCCR1B, BIT(CS10));
		bit_set(TCCR1B, BIT(CS12) | BIT(CS11));
		break;
	case EXT_RISE:
		/* set CS12 CS11 CS10 */
		bit_set(TCCR1B, BIT(CS12) | BIT(CS11) | BIT(CS10));
		break;
	default:
		break;
	}

	sei();		// Enable interrupts
}
