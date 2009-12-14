#include <stdio.h>
#include <string.h>
#include "macro.h"
#include "lcd.h"

#define LCD_PORT	PORTC
#include <util/delay.h>

#define LCD_PORT_DIR	DDRC

#define LCD_E	(1 << 3)
#define LCD_RS	(1 << 2)
#define LCD_DATS	4
#define LCD_DATMASK	0xf

#define DATASIZE 17

const static uint8_t *hex_table = "0123456789abcdef";

void lcd_put_4bit(uint8_t bitadata);
void lcd_init2(void);

void lcd_init( void )
{
	_delay_ms(15);
	LCD_PORT_DIR = LCD_E | LCD_RS | (LCD_DATMASK<<LCD_DATS);

	cbi( LCD_PORT, LCD_RS );
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
	sbi( LCD_PORT, LCD_RS );

	lcd_init2();
	
}

void lcd_position(uint8_t tx, uint8_t ty)
{
	cbi( LCD_PORT, LCD_RS );
	lcd_put_ch(0x80 | tx | (0x40 * ty ));
	sbi( LCD_PORT, LCD_RS );
}

void lcd_put_4bit( uint8_t bitdata)
{
	cbi( LCD_PORT, LCD_DATMASK << LCD_DATS );
	sbi( LCD_PORT, (LCD_DATMASK & bitdata) << LCD_DATS );
	sbi( LCD_PORT, LCD_E );
	_delay_ms(1);

	cbi( LCD_PORT, LCD_E );
	_delay_ms(1);
}


/**** “¯ŠúŒ^•\Ž¦ŠÖ” ************************************************/
void lcd_put_ch(uint8_t ch)
{
	lcd_put_4bit(ch >> 4);
	lcd_put_4bit(LCD_DATMASK & ch);

	_delay_ms(1);
}

void lcd_put_hex2ch(uint8_t ch)
{
	lcd_put_ch( hex_table[ (ch >> 4) & 0xf ] );
	lcd_put_ch( hex_table[ ch & 0xf ] );
}

void lcd_put_str( uint8_t *str)
{
	while(*str != 0)
	{
		lcd_put_ch( *str );
		str++;
	}
}

void lcd_clear_all( void ){
	lcd_clear_lower();
	lcd_clear_upper();
}
void lcd_clear_upper( void ){
	lcd_position(0,0);
	lcd_put_str(LCD_BLANK);
}
void lcd_clear_lower( void ){
	lcd_position(0,1);
	lcd_put_str(LCD_BLANK);
}


/**** ”ñ“¯ŠúŒ^•\Ž¦ŠÖ” ************************************************/

static uint8_t display_data[LCD_ROW][DATASIZE];
static uint8_t pos[LCD_ROW];
static uint8_t count[LCD_ROW];
uint8_t lcd_dirty[LCD_ROW];

#define lcd_set_dirty( row ) do{ \
	lcd_dirty[row] = 1; \
	count[row] = 0; \
} while(0)

#define lcd_clear_dirty( row ) do{ \
	lcd_dirty[row] = 0; \
	count[row] = 0; \
} while(0)

void lcd_display_row( uint8_t row );

void lcd_init2(){
	memset(display_data,' ',LCD_ROW*DATASIZE);
	memset(lcd_dirty,0,LCD_ROW);
	memset(pos,0,LCD_ROW);
	memset(count,0,LCD_ROW);
}

void lcd_set_data( uint8_t *data, uint8_t row, uint8_t col, size_t len ){
	memcpy(&display_data[row][col], data, len);
	lcd_set_dirty(row);
}

void lcd_set_hex8( uint8_t hex, uint8_t row, uint8_t col ){
   static uint8_t buf[2];
   buf[0] = hex_table[ (hex >> 4) & 0xf ];
   buf[1] = hex_table[ hex & 0xf ];
   lcd_set_data( buf, row, col, 2 );
}

void lcd_set_hex16( uint16_t hex, uint8_t row, uint8_t col ){
   uint8_t *p = (uint8_t *)&hex;
   lcd_set_hex8( *(p+1), row, col );
   lcd_set_hex8( *p, row, col+2 );
}

void lcd_set_clear( uint8_t row ){
   lcd_set_data( LCD_BLANK, row, 0, LCD_COL );
}

void lcd_display(void){
	if( lcd_dirty[LCD_UPPER] )
		lcd_display_row( LCD_UPPER );
	if( lcd_dirty[LCD_LOWER] )
		lcd_display_row( LCD_LOWER );
}

static uint8_t last_display_row = 0;
void lcd_display_row( uint8_t row ){
	if( row != last_display_row || pos[row] == 0 ){
		lcd_position(pos[row], row);
		last_display_row = row;
	}
	lcd_put_ch(display_data[row][(uint8_t)pos[row]]);
	pos[row] = (pos[row]+1) & 0xf;
	if( ++count[row] >= LCD_COL ){
		lcd_clear_dirty(row);
	}
}



