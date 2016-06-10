#ifndef UART_H
#define UART_H
//#define BAUD 9600

/* standard c include */
#include <stdio.h>
/* AVR-libc include */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
/* User-lib include */
#include <bits.h>

void uart_init( void );
void uart_rx_interrupt_enable( void );
void uart_rx_interrupt_disable( void );
void uart_tx_interrupt_enable( void );
void uart_tx_interrupt_disable( void );
void uart_putchar(uint8_t c, FILE *stream);
uint8_t uart_getchar(FILE *stream);

static FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static FILE uart_input	= FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
#endif
