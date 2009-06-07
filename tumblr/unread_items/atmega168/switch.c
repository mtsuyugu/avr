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


/**** �������� *****************************************************
 *
 * �X�C�b�`�̗��p�󋵂ɂ��
 *  GEN_PORT_GET_FUNC, NUM_SW, SW_MAP, sw_port_init
 * ��K�؂ɏC�����邱��
 *
 ********************************************************************/

/* �X�C�b�`�Ƃ��Ďg���|�[�g��錾����B1 �ł��g���Ă���|�[�g�̖��O�΂��Đ錾���邱�ƁB */
GEN_PORT_GET_FUNC( B );


/* �X�C�b�`�̐��ƃX�C�b�`�̒�` SW_MAP �̓Y�������v���O�������ł̃X�C�b�`�̔ԍ��ƂȂ� */
#define NUM_SW 1
static char sw_prev_status[NUM_SW]; // 0: OFF, 1:ON
const SW_MAP sw_map[] = { 
	{_portB_get, 0}
};

/* �|�[�g�̏������A���g�p�|�[�g�����͂ɂ��āA�v���A�b�v��L���ɂ��Ă������� */
void sw_port_init( void ){
	// pull up all ports
	DDRB = 0x00;
	PORTB = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;


}
/**** �����܂� *****************************************************/


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

