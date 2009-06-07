#include <ctype.h>
#include <string.h>
#include "lcd.h"
#include "tumblr.h"

#define WAIT_LEFT_BRACKET 0
#define WAIT_DIGIT_OR_RIGHT_BRACKET 1

#define TUMBLR_NOT_RECEIVED_YET -1
#define TUMBLR_STR "Tumblr"
#define TUMBLR_STR_W16 "Tumblr          "
#define TUMBLR_DIGGIN  "Let's diggin'   "

#define LOW_DISPLAY_OFF 0
#define LOW_DISPLAY_ON  1

static int state;
static int num;
static int low_display = 0;
static char buf[32];

int transition_0( char c );
int transition_1( char c );
void do_action( int num );

static int (*state_transition_func_table[])(char) = {
	transition_0,
	transition_1
};

void tumblr_state_machine_init( void ){
	state = WAIT_LEFT_BRACKET;
	num = 0;
}

void tumblr_display_init( void ){
	low_display = LOW_DISPLAY_OFF;
	lcd_position(0,0);
	lcd_put_str(TUMBLR_STR);
}

void tumblr_display_reset( void ){
	low_display = LOW_DISPLAY_OFF;
	lcd_set_data( TUMBLR_STR_W16, LCD_UPPER, 0, LCD_COL );
	lcd_set_data( LCD_BLANK, LCD_LOWER, 0, LCD_COL );
}

void tumblr_state( char c ){
	int num = state_transition_func_table[state](c);
	do_action( num );
}

int transition_0( char c ){
	if( c == '[' ){
		state = WAIT_DIGIT_OR_RIGHT_BRACKET;
	}
	return TUMBLR_NOT_RECEIVED_YET;
}

int transition_1( char c ){
	int result = TUMBLR_NOT_RECEIVED_YET;
	if( isdigit(c) ){
		num = num * 10 + c - '0';
		return result;
	}
	if( c == ']' ){
		result = num;
	}
	tumblr_state_machine_init();
	return result;
}

void do_action( int num ){
	if( num == TUMBLR_NOT_RECEIVED_YET ){
		return;
	}
	char *p;
	if( num == 0){
		p = TUMBLR_STR_W16;
		if( low_display != LOW_DISPLAY_OFF ){
			lcd_set_data( LCD_BLANK, LCD_LOWER, 0, LCD_COL );
			low_display = LOW_DISPLAY_OFF;
		}
	}
	else{
		int len = sprintf( buf, "(%d) " TUMBLR_STR, num );
		memset( buf+len, ' ', LCD_COL-len );
		p = buf;
		if( low_display != LOW_DISPLAY_ON ){
			lcd_set_data( TUMBLR_DIGGIN, LCD_LOWER, 0, LCD_COL );
		low_display = LOW_DISPLAY_ON;
		}
	}
	lcd_set_data( p, LCD_UPPER, 0, LCD_COL );
}


