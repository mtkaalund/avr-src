#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <bits.h>

uint16_t adc_read( uint8_t channel );

int main(void)
{
	/* Set it to output */
	DDRB   |= BIT(PB2);
	/* Clear on OC1B compare match */
	TCCR1A |= BIT(COM1B1);
	/* Fast PWM 10-bit */
	TCCR1A |= BIT(WGM11) | BIT(WGM10);
	TCCR1B |= BIT(WGM12);//BIT(WGM13) | BIT(WGM12);
	/* Prescale selected*/
//	TCCR1B |= BIT(CS12) | BIT(CS10);
//	TCCR1B |= BIT(CS12); //fcpu/64
//	TCCR1B |= BIT(CS11) | BIT(CS10);
	TCCR1B |= BIT(CS10);
	/* Set output compare register 1B */
	OCR1B = 0x0000;

	/* ADC */
	/* 	AVCC
	*/
	ADMUX |= BIT(REFS0);
	ADCSRA |= BIT(ADPS2) | BIT(ADPS1) | BIT(ADPS0);
	ADCSRA |= BIT(ADSC) | BIT(ADEN);

	uint8_t adc_count = 0;
	uint16_t adc_value = 0;
	uint16_t adc_old = 0;
	sei();

	for(;;)
	{
		_delay_ms(50);
		adc_value += adc_read(0);
		adc_count++;

		if( adc_count == 16 )
		{
			adc_value /= 16;
			if( adc_value != adc_old )
			{	
				OCR1B = adc_value;
				adc_old = adc_value;
			}
			adc_count = 0;
		}
	}
	
	return 0;
}

uint16_t adc_read( uint8_t channel )
{
	ADMUX &= 0xF0;
	ADMUX |= channel;

	ADCSRA |= BIT(ADSC);

	while( bit_get(ADCSRA, BIT(ADSC) ) != 0 );

	return ADCW;
}
