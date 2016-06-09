/* #include <stdio.h> */
#include <avr/io.h>
#include <util/delay.h>
#include <bits.h>

#define PG_DELAY 	1000
#define LED_PIN 	 5

/* defines the baud rate */
#define BAUD		9600

#define VERSION		"0.0.1"
/*
#include <util/setbaud.h>
#include <avr/interrupt.h>
*/
#include <avr/version.h>

#include "uart.h"
#include "timer1_ctc.h"

void print_about(void);
/*
void uart_init(void);
void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);
*/
/*
void timer1_ctc_init(void);
void timer1_ctc_set(unsigned int foc1a);
*/
/*
static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE uart_input	= FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
*/
/* date struct */
typedef struct {
	char sec;
	char min;
	char hour;
	char day;
	char mon;
	int  year;
} date_t;

volatile date_t date;
volatile int count;
volatile char rx_data;

int main(void)
{
	unsigned int values[] = {4545, 4290, 4049, 3822, 3607, 3405, 3214, 3033, 2863, 2702, 2551, 2407, 2272, 2145, 2024, 1911, 1803, 1702, 1607, 1516, 1431, 1351, 1275, 1203, 1136, 1072, 1012, 955, 901, 851, 803, 758, 715, 675, 637, 601, 568, 536, 506, 477, 450, 425, 401, 379, 357, 337, 318, 300, 284, 268, 253, 238, 225, 212, 200, 189, 178, 168, 159, 150, 142, 134, 126, 119, 112, 106, 100, 94, 89, 84, 79, 75, 71, 67, 63, 59, 56, 53, 50, 47, 44, 42, 39, 37, 35, 33, 31, 29 } ;
	char value_size = 88;
	char value_count = 0;
	char pre_count = 0;

	date.sec = 0;
	date.min = 0;
	date.hour = 0;
	date.day = 0;
	date.mon = 0;
	date.year = 0;
	
	/* init */
	rx_data = 0;
	uart_init();
	stdout	= &uart_output;
	stdin	= &uart_input;
	uart_rx_interrupt_enable();
//	UCSR0B |= (1 << RXCIE0);
	/* init counter */
	count = 0;
	timer1_ctc_init();
/*
	TCCR1B |= (1 << WGM12); //Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A);	//Enable CTC interrupt
	sei();			//Enable global interrupt
*/
	Timer1Prescale scale = CLK64;
	timer1_ctc_set_prescale( scale );
	timer1_ctc_set_value( 124 ); //15624 );
	sei();			//Enable global interrupt
	/* Sets port b pin (LED_PIN) to output */
	bit_set(DDRB, BIT(LED_PIN));
	bit_clear(PORTB, BIT(LED_PIN));
	_delay_ms(100);
	bit_set(PORTB, BIT(LED_PIN));
	_delay_ms(100);
	bit_clear(PORTB, BIT(LED_PIN));

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
			case 's':	
				value_count++;
				if( value_count >= value_size )
					value_count = 0;

				printf("Setting timer1 to %d, count is %d\n", values[ value_count ], value_count);
				timer1_ctc_set_value( values[ value_count ] ); //15624 );
				break;

			case 'v':
				print_about();
				break;
			case 'd':

				printf("time is %d:%d:%d of %d/%d-%d\n", date.hour, date.min, date.sec, date.day, date.mon, date.year);
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
	printf("TimerAVR version: %s\n", VERSION);
	printf("build with AVR LIBC version: %s\n", __AVR_LIBC_VERSION_STRING__);
}
/*
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

void uart_putchar(char c, FILE *stream)
{
	if(c == '\n')
	{
		uart_putchar('\r', stream);
	}

	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
}

char uart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}
*/
/*
void timer1_ctc_init(void)
{

	TCCR1B |= (1 << WGM12); //Configure timer 1 for CTC mode
	TIMSK1 |= (1 << OCIE1A);	//Enable CTC interrupt
	sei();			//Enable global interrupt
}

void timer1_ctc_set(unsigned int foc1a)
{
*/
/*
	N = { 1, 8, 64, 256, 1024 }
	f_clk = f_cpu
	Focna = f_clk / ( 2 * N * (1 + OCRnA ) )
=>	(1 + OCRnA) * Focna = f_clk / ( 2 * N )
=>	(1 + OCRnA) = f_clk / ( 2 * N * Focna )
=>	OCRnA = f_clk / ( 2 * N * Focna ) - 1

	OCRnA = 16000000 / ( 2 * 64 * 1000 ) - 1 = 
*/
/*
	OCR1A = foc1a;// 15624;		//Count to
	TCCR1B |= (BIT(CS10) | BIT(CS12)); //Start timer at Fcpu/64
}
*/

ISR(TIMER1_COMPA_vect)
{
	bit_flip(PORTB, BIT(LED_PIN));
	date.sec += 1;
	
	if(date.sec % 60 == 0)
	{
		date.sec = 0;
		date.min += 1;

		if(date.min % 60 == 0)
		{
			date.min = 0;
			date.hour += 1;

			if(date.hour % 24 == 0)
			{
				date.hour = 0;
				date.day += 1;

				if(date.day % 30 == 0)
				{
					date.mon += 1;

					if(date.mon % 12 == 0)
					{
						date.year += 1;
					}
				}
			}
		}
	}
}

ISR(USART_RX_vect)
{
	rx_data = 1;
}
