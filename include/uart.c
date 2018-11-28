#include "uart.h"
// This is code for avr microprocessors
// atmega48p
// atmega88p
// atmega168p
// atmega328p
// and others with same uart pin out
// Remember to create check if support cpus are the one who are being compiled to
// Remember to set F_CPU and BAUD before including
// If you want to use this with interrupt based communication
// then set UART_ISR

static inline void uart_init()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	bit_set( UCSR0A, BIT( U2X ) );
#else
	bit_clear( UCSR0A, BIT( U2X ) );
#endif
#ifndef UART_ISR
	bit_set( UCSR0B, BIT( RXCIE0 ) );
#endif	
}

static inline void uart_putc( unsigned char  c ) 
{
	// Here we check if has a 'new line' char
	// and replacing it with a '\r'
	if( c == '\n' )
		uart_putc( '\r' );

	loop_until_bit_is_set( UCSR0A, UDRE0 );
	UDR0 = c;
}

static inline void uart_puts( unsigned char *s )
{
	while( *s ) {
		uart_putc( *s++ );
	}
	uart_putc('\n');
}

static inline unsigned char uart_getc( void )
{
	// Wait until data is there
	loop_until_bit_is_set( UCSR0A, UDRE0 );
	return UDR0;
}
