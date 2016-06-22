#ifndef ADC_SINGLE_H
#define ADC_SINGLE_H

#include <avr/io.h>
#include <util/delay.h>
#include <bits.h>

/*	ADC Conversion Result
	=====================
		Vin * 1024
	ADC = -------------
		  Vref


		ADC * Vref
	Vin = -------------
		  1024
*/
typedef enum { AREF, AVCC, VREF } REF;
typedef enum { P2, P4, P8, P16, P32, P64, P128 } PRE;

void adc_enable( void );
void adc_disable( void );
void adc_prescale( PRE _pre);
void adc_reference( REF _ref);
uint16_t adc_read( uint8_t channel );

#endif
