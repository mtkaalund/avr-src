#include <avr/io.h>
#include <util/delay.h>
#include <bits.h>

#include "uart.h"
#include "adc_single.h"

#define LED_PIN		PB5
#define LED_PORT	PORTB
#define LED_DDR		DDRB

int main(void)
{
	uint16_t adc = 0;

	uart_init();

	stdout	= &uart_output;
	stdin	= &uart_input;
	
	/* init set led to output */
	bit_set(LED_DDR, BIT(LED_PIN));

	adc_reference( AVCC );

	/* PRESCALE */
	adc_prescale(P128);
	adc_enable();
	ADCSRA |= BIT(ADSC);

	uint8_t count = 0;

	for(;;)
	{
		bit_set(LED_PORT, BIT(LED_PIN));
		count++;
		adc += adc_read(0);

		if(count >= 16)
		{
			adc /= 16;
			count = 0;
			printf("ADC result: %d\n", adc);
		}
		_delay_ms(50);

		bit_clear(LED_PORT, BIT(LED_PIN));
		_delay_ms(50);
	}
	
	return 0;
}
