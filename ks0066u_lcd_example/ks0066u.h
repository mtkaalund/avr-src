#ifndef KS0066U_H
#define KS0066U_H

#include <avr/io.h>
#include <util/delay.h>

#define LCD_FUNC_PORT 
#define LCD_RS
#define LCD_RW
#define LCD_EN

#define LCD_DATA_PORT
#ifdef LCD_8BIT
#define LCD_D0
#define LCD_D1
#define LCD_D2
#define LCD_D3
#endif
#define LCD_D4
#define LCD_D5
#define LCD_D6
#define LCD_D7

void ks0066u_init( void );
void ks0066u_nibble( void );

#endif
