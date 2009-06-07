#include <string.h> // for memset
#include <avr/io.h>
#include "macro.h"
#include "switch.h"

#define GEN_PORT_GET_FUNC( PORTID ) \
	char _port##PORTID##_get(char bitnum) \
	{ \
		if( ( PIN##PORTID & _BV(bitnum) ) == 0 ) \
			return SW_ON; \
		else \
			return SW_OFF; \
	} \

typedef struct _sw_map{
	char (* port_get)(char);
	char bitnum;
} SW_MAP;


/**** ここから *****************************************************
 *
 * スイッチの利用状況により
 *  GEN_PORT_GET_FUNC, NUM_SW, SW_MAP, sw_port_init
 * を適切に修正すること
 *
 ********************************************************************/

/* スイッチとして使うポートを宣言する。1 つでも使っているポートの名前対して宣言すること。 */
GEN_PORT_GET_FUNC( B );


/* スイッチの数とスイッチの定義 SW_MAP の添え字がプログラム内でのスイッチの番号となる */
#define NUM_SW 1
static char sw_prev_status[NUM_SW]; // 0: OFF, 1:ON
const SW_MAP sw_map[] = { 
	{_portB_get, 0}
};

/* ポートの初期化、未使用ポートも入力にして、プルアップを有効にしておくこと */
void sw_port_init( void ){
	// pull up all ports
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;


}
/**** ここまで *****************************************************/


void sw_init(void)
{
	sw_port_init();
	memset(sw_prev_status, 0, NUM_SW);
}


int sw_get_status( char swno, char *out ){
	char (* port_get)(char bitnum) = sw_map[(int)swno].port_get;
	char bitnum = sw_map[(int)swno].bitnum;
	char now = port_get(bitnum);
	*out = now;
	if( sw_prev_status[ (int)swno ] != now ){
		sw_prev_status[ (int)swno ] = now;
		return 1;
	}
	return 0;
}

