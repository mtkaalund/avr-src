#include "uart.h"

/*
uint16_t uart_calc_baud(uint16_t baud)
{
	uint16_t ubbrr0 = (( F_CPU / ( 16UL * baud) ) - 1);

	

	return ubbrr0;
}
*/

void uart_init(void)
{
	UBRR0H	=	UBRRH_VALUE;
	UBRR0L	=	UBRRL_VALUE;
	
	#if USE_2X
		UCSR0A |= BIT(U2X0);
	#else
		UCSR0A &= ~(BIT(U2X0));
	#endif

	UCSR0C	=	BIT(UCSZ01) | BIT(UCSZ00);
	UCSR0B	=	BIT(RXEN0)  | BIT(TXEN0);
}

void uart_rx_interrupt_enable( void )
{
	cli();
	bit_set(UCSR0B, BIT(RXCIE0));
	sei();
}

void uart_rx_interrupt_disable( void )
{
	cli();
	bit_clear(UCSR0B, BIT(RXCIE0));
	sei();
}

void uart_tx_interrupt_enable( void )
{
	cli();
	bit_set(UCSR0B, BIT(TXCIE0));
	sei();
}

void uart_tx_interrupt_disable( void )
{
	cli();
	bit_clear(UCSR0B, BIT(TXCIE0));
	sei();
}

void uart_putchar(uint8_t c, FILE *stream)
{
	if(c == '\n')
	{
		uart_putchar('\r', stream);
	}

	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

uint8_t uart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}
