#include "adc_single.h"

void adc_enable( void )
{
	bit_set( ADCSRA, BIT(ADEN));
}

void adc_disable( void )
{
	bit_clear( ADCSRA, BIT(ADEN) );
}

void adc_prescale( PRE _pre)
{
	switch( _pre )
	{
	case P2:
		bit_clear(ADCSRA, BIT(ADPS2));
		bit_clear(ADCSRA, BIT(ADPS1));
		bit_set(ADCSRA, BIT(ADPS0));
	break;
	case P4:
		bit_clear(ADCSRA, BIT(ADPS2));
		bit_clear(ADCSRA, BIT(ADPS0));
		bit_set( ADCSRA, BIT(ADPS1));
	break;
	case P8:
		bit_clear(ADCSRA, BIT(ADPS2));
		bit_set(ADCSRA, BIT(ADPS1));
		bit_set(ADCSRA, BIT(ADPS0));
	break;
	case P16:
		bit_set(ADCSRA, BIT(ADPS2));
		bit_clear(ADCSRA, BIT(ADPS1));
		bit_clear(ADCSRA, BIT(ADPS0));
	break;
	case P32:
		bit_set(ADCSRA, BIT(ADPS2));
		bit_set(ADCSRA, BIT(ADPS0));
		bit_clear(ADCSRA, BIT(ADPS1));
	break;
	case P64:
		bit_set(ADCSRA, BIT(ADPS2));
		bit_set(ADCSRA, BIT(ADPS1));
		bit_clear(ADCSRA, BIT(ADPS0));
	break;
	case P128:
		bit_set(ADCSRA, BIT(ADPS2));
		bit_set(ADCSRA, BIT(ADPS1));
		bit_set(ADCSRA, BIT(ADPS0));
	break;
	}
}

void adc_reference( REF _ref)
{
	switch( _ref )
	{
	case AREF:
		bit_clear(ADMUX, BIT(REFS1));
		bit_clear(ADMUX, BIT(REFS0));
	break;

	case AVCC:
		bit_clear(ADMUX, BIT(REFS1));
		bit_set(ADMUX, BIT(REFS0));
	break;

	case VREF:
		bit_set(ADMUX, BIT(REFS1));
		bit_set(ADMUX, BIT(REFS0));
	break;

	default:
		adc_reference( AVCC );
	break;
	};

}

uint16_t adc_read( uint8_t channel )
{
	ADMUX &= 0xF0;
	ADMUX |= channel;

	ADCSRA |= BIT(ADSC); /* single conversion */

	while( bit_get(ADCSRA, BIT(ADSC)) != 0 ); /* wait until complete */

	return ADCW; 
}

