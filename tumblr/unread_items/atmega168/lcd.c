#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "macro.h"
#include "lcd.h"

#define LCD_PORT	PORTD
#include <util/delay.h>

#define LCD_PORT0	DDRD

#define LCD_E	(1 << 3)
#define LCD_RS	(1 << 2)
#define LCD_DATS	4
#define LCD_DATMASK	0xf

#define DATASIZE 17

void lcd_put_4bit(char bitadata);
void lcd_init2(void);

void lcd_init( void )
{
	_delay_ms(15);
	LCD_PORT0 = LCD_E | LCD_RS | (LCD_DATMASK<<LCD_DATS);

	BIT_CLEAR( LCD_PORT, LCD_RS );
	lcd_put_4bit( 0x3 );
	_delay_ms(5);
	lcd_put_4bit( 0x3 );
	_delay_ms(1);
	lcd_put_4bit( 0x3 );
	lcd_put_4bit( 0x2 );

	lcd_put_ch( 0x28 );
	lcd_put_ch( 0x0C );
	lcd_put_ch( 0x06 );
	lcd_put_ch( 0x01 );
	_delay_ms(2);
	BIT_SET( LCD_PORT, LCD_RS );

	lcd_init2();
	
}

void lcd_position(char tx, char ty)
{
	BIT_CLEAR( LCD_PORT, LCD_RS );
	lcd_put_ch(0x80 | tx | (0x40 * ty ));
	BIT_SET( LCD_PORT, LCD_RS );
}

void lcd_put_4bit( char bitdata)
{
	BIT_CLEAR( LCD_PORT, LCD_DATMASK << LCD_DATS );
	BIT_SET( LCD_PORT, (LCD_DATMASK & bitdata) << LCD_DATS );
	BIT_SET( LCD_PORT, LCD_E );
	_delay_ms(1);

	BIT_CLEAR( LCD_PORT, LCD_E );
	_delay_ms(1);
}


/**** “¯ŠúŒ^•\Ž¦ŠÖ” ************************************************/
int lcd_put_ch(char ch)
{
	lcd_put_4bit(ch >> 4);
	lcd_put_4bit(LCD_DATMASK & ch);

	_delay_ms(1);
	return 0;
}

int lcd_put_hex2ch(char ch)
{
	static char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E' };
	lcd_put_ch( hex[ ch >> 4 ] );
	lcd_put_ch( hex[ ch & 0xf ] );
	return 0;
}

void lcd_put_str( char *str)
{
	while(*str != 0)
	{
		lcd_put_ch( *str );
		str++;
	}
}

int lcd_put_ch2( char ch, FILE *fp)
{
	lcd_put_ch(ch);
	return 0;
}

void lcd_clear_all( void ){
	lcd_clear_lower();
	lcd_clear_upper();
}
void lcd_clear_upper( void ){
	lcd_position(0,0);
	lcd_put_str("                ");
}
void lcd_clear_lower( void ){
	lcd_position(0,1);
	lcd_put_str("                ");
}


/**** ”ñ“¯ŠúŒ^•\Ž¦ŠÖ” ************************************************/

static char display_data[LCD_ROW][DATASIZE];
static char pos[LCD_ROW];
static char count[LCD_ROW];
char lcd_dirty[LCD_ROW];

#define lcd_set_dirty( row ) do{ \
	lcd_dirty[row] = 1; \
	count[row] = 0; \
} while(0)

#define lcd_clear_dirty( row ) do{ \
	lcd_dirty[row] = 0; \
	count[row] = 0; \
} while(0)

void lcd_display_row( int row );

void lcd_init2(){
	memset(display_data,0,LCD_ROW*DATASIZE);
	memset(lcd_dirty,0,LCD_ROW);
	memset(pos,0,LCD_ROW);
	memset(count,0,LCD_ROW);
}

void lcd_set_data( char *data, int row, int pos, size_t len ){
	memcpy(&display_data[row][pos], data, len);
	lcd_set_dirty(row);
}

void lcd_display(void){
	if( lcd_dirty[LCD_UPPER] )
		lcd_display_row( LCD_UPPER );
	if( lcd_dirty[LCD_LOWER] )
		lcd_display_row( LCD_LOWER );
}

static int last_display_row = 0;
void lcd_display_row( int row ){
	if( row != last_display_row || pos[row] == 0 ){
		lcd_position(pos[row], row);
		last_display_row = row;
	}
	lcd_put_ch(display_data[row][(int)pos[row]]);
	pos[row] = (pos[row]+1) & 0xf;
	if( ++count[row] >= LCD_COL ){
		lcd_clear_dirty(row);
	}
}



