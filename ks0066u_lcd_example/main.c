/*
	Example file for LCD display
	16 char 1 line
	ks0066u

	pin no		symbol
	1		gnd
	2		vdd (supply logic)
	3		V0  (supply lcd)
	4		RS (register selection)
	5		RW (read/write)
	6		Enable
	7		DB0
	8		DB1
	9		DB2
	10		DB3
	11		DB4
	12		DB5
	13		DB6
	14		DB7
*/
#include <avr/io.h>
#include <util/delay.h>
#include <bits.h>

/* helper macros */
#define DDR(x) (*(&x - 1) )
#define PIN(x) (*(&x - 2) )

/* defining delays for lcd */
#define LCD_DELAY_ENABLE_US	0.5 /* 500 ns */
#define LCD_DELAY_DATA_US	43.0
#define LCD_DELAY_FUNC_US	39.0
#define LCD_DELAY_MODE_MS	1.53
#define LCD_DELAY_BOOT_MS	30
/* mapping function to port */
#define LCD_FUNC_PORT	PORTC	
#define LCD_EN		0
#define LCD_RS		1
#define LCD_RW		2
/* mapping lower bytes to port */
#define LCD_LSB_PORT	PORTB
#define LCD_LSB_0	0
#define LCD_LSB_1	1
#define LCD_LSB_2	2
#define LCD_LSB_3	3
/* mapping upper bytes to port */
#define LCD_MSB_PORT	PORTD
#define LCD_MSB_0	4
#define LCD_MSB_1	5
#define LCD_MSB_2	6
#define LCD_MSB_3	7

void lcd_send( uint8_t data );
void lcd_enable( void );
void lcd_cmd( uint8_t cmd );
void lcd_set_data( uint8_t data );
uint8_t lcd_get_data( void );
void lcd_set_cgram( uint8_t addr );
void lcd_set_ddram( uint8_t addr );


int main(void)
{
	for(;;)
	{
	}
	
	return 0;
}

void lcd_send( uint8_t data )
{
	bit_set( DDR( LCD_LSB_PORT ), 	BIT( LCD_LSB_0 ) | BIT( LCD_LSB_1) \
					| BIT( LCD_LSB_2 ) | BIT( LCD_LSB_3 ) );
	bit_set( DDR( LCD_MSB_PORT ), 	BIT( LCD_MSB_0 ) | BIT( LCD_MSB_1) \
					| BIT( LCD_MSB_2 ) | BIT( LCD_MSB_3 ) );

	/* sending lower bytes */
	if( ( data & BIT(0) ) != 0 ) bit_set( LCD_LSB_PORT, BIT( LCD_LSB_0 ) );
	if( ( data & BIT(1) ) != 0 ) bit_set( LCD_LSB_PORT, BIT( LCD_LSB_1 ) );
	if( ( data & BIT(2) ) != 0 ) bit_set( LCD_LSB_PORT, BIT( LCD_LSB_2 ) );
	if( ( data & BIT(3) ) != 0 ) bit_set( LCD_LSB_PORT, BIT( LCD_LSB_3 ) );
	/* sending upper bytes */
	if( ( data & BIT(4) ) != 0 ) bit_set( LCD_MSB_PORT, BIT( LCD_MSB_0 ) );
	if( ( data & BIT(5) ) != 0 ) bit_set( LCD_MSB_PORT, BIT( LCD_MSB_1 ) );
	if( ( data & BIT(6) ) != 0 ) bit_set( LCD_MSB_PORT, BIT( LCD_MSB_2 ) );
	if( ( data & BIT(7) ) != 0 ) bit_set( LCD_MSB_PORT, BIT( LCD_MSB_3 ) );
}

void lcd_enable( void )
{
	bit_set( LCD_FUNC_PORT, BIT( LCD_EN ) );
	_delay_us( LCD_DELAY_ENABLE_US );
	bit_clear( LCD_FUNC_PORT, BIT( LCD_EN ) );
}

void lcd_cmd( uint8_t cmd )
{
	/* instruction data set from datasheet */
	bit_clear( LCD_FUNC_PORT, BIT( LCD_RS ) );
	lcd_send( cmd );
	_delay_us( LCD_DELAY_FUNC_US );
	lcd_enable();
}

void lcd_set_data( uint8_t data )
{
	bit_set( LCD_FUNC_PORT, BIT( LCD_RS ) );
	bit_clear( LCD_FUNC_PORT, BIT( LCD_RW ) );

	lcd_send( data );
	_delay_us( LCD_DELAY_DATA_US );
	lcd_enable();
}

uint8_t lcd_get_data( void )
{
	uint8_t data = 0;
	/* we need to set it to in put */
	bit_clear( DDR( LCD_LSB_PORT ), BIT( LCD_LSB_0 ) | BIT( LCD_LSB_1) \
					| BIT( LCD_LSB_2 ) | BIT( LCD_LSB_3 ) );
	bit_clear( DDR( LCD_MSB_PORT ), BIT( LCD_MSB_0 ) | BIT( LCD_MSB_1) \
					| BIT( LCD_MSB_2 ) | BIT( LCD_MSB_3 ) );

	bit_set( LCD_FUNC_PORT, BIT( LCD_RS ) );
	bit_set( LCD_FUNC_PORT, BIT( LCD_RW ) );

	lcd_enable();

	if( (PIN(LCD_LSB_PORT) & BIT(LCD_LSB_0)) != 0 ) bit_set(data, BIT(0));
	if( (PIN(LCD_LSB_PORT) & BIT(LCD_LSB_1)) != 0 ) bit_set(data, BIT(1));
	if( (PIN(LCD_LSB_PORT) & BIT(LCD_LSB_2)) != 0 ) bit_set(data, BIT(2));
	if( (PIN(LCD_LSB_PORT) & BIT(LCD_LSB_3)) != 0 ) bit_set(data, BIT(3));
	
	if( (PIN(LCD_MSB_PORT) & BIT(LCD_MSB_0)) != 0 ) bit_set(data, BIT(4));
	if( (PIN(LCD_MSB_PORT) & BIT(LCD_MSB_1)) != 0 ) bit_set(data, BIT(5));
	if( (PIN(LCD_MSB_PORT) & BIT(LCD_MSB_2)) != 0 ) bit_set(data, BIT(6));
	if( (PIN(LCD_MSB_PORT) & BIT(LCD_MSB_3)) != 0 ) bit_set(data, BIT(7));
	return data;
}

void lcd_set_cgram( uint8_t addr )
{
	uint8_t t_addr;
	bit_clear( LCD_FUNC_PORT, BIT( LCD_RW ) );
	t_addr = bit_set(addr, BIT( 6 ) );
	t_addr = bit_clear(addr, BIT( 7 ) );
	lcd_cmd( t_addr );
	lcd_enable();
}

void lcd_set_ddram( uint8_t addr )
{
	uint8_t t_addr;
	bit_clear( LCD_FUNC_PORT, BIT( LCD_RW ) );
	t_addr = bit_set(addr, BIT( 7 ) );
	lcd_cmd( t_addr );
	lcd_enable();
}
