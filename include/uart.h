#ifndef _UART_H_
#define _UART_H_
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
#include <util/setbaud.h>

// Initialize the uart
static inline void uart_init( void );

// send out a unsigned char
static inline void uart_putc( unsigned char  c );
// send out a strings of chars
static inline void uart_puts( unsigned char *s );
// receive a char
static inline unsigned char uart_getc( void );

#endif
