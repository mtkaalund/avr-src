/* #include <stdio.h> */
#include <avr/io.h>
#include <util/delay.h>
#include <bits.h>

/* defines the baud rate */
//#define BAUD		9600

#define VERSION		"0.0.2"
#include <avr/version.h>

#include <uart.h>
#include "timer1_ctc.h"

void print_about(void);
void print_help(void);

volatile rx_data = 0;

int main(void)
{
	/* init */
	uart_init();

	stdout	= &uart_output;
	stdin	= &uart_input;

	char input;
	/* program loop */
	for(;;)
	{
		if(rx_data)
		{
			rx_data = 0;
			input = getchar();
		
			switch(input)
			{
			case '\n':
			case '\r':
				break;
			case '?':
			case 'h':
				print_help();
				break;
			case 'v':
				print_about();
				break;
			default:
				printf("input is '%c'\n", input);
				break;
			}
		}
	}
	
	return 0;
}

void print_about(void)
{
	printf("UartExample version: %s\n", VERSION);
	printf("build with AVR LIBC version: %s\n", __AVR_LIBC_VERSION_STRING__);
}

void print_help(void)
{
	printf("Send 'h' to get help menu\n");
	printf("Send 'v' to get the version on libc used\n");
}

ISR(USART_RX_vect)
{
	rx_data = 1;
}
