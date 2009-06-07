#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "macro.h"
#include "swatch.h"

#define PITCH 100
#define PRESC 64
#define INTRCOUNT (0x10000-((F_CPU / PRESC) / PITCH ))

#define SW_PORT PORTB
#define SW_DDR DDRB
#define SW_PIN PINB
#define SW_START 0

long cnt;

SIGNAL (TIMER1_OVF_vect)
{
	TCNT1 = INTRCOUNT;
	cnt++;
}

void timer1_init(void)
{
	TCCR1A = 0;
	TCCR1B = 3;
	
	BIT_SET( TIFR1, _BV(TOV1) );
	BIT_SET( TIMSK1, _BV(TOIE1) );
}

void timer1_reset(void)
{
	cnt=0;
	TCNT1 = INTRCOUNT;
}

long timer1_get_cnt(void)
{
	return cnt;
}

void disable_timer1_interrupt(void){
	// cli();
	BIT_CLEAR( TIMSK1, _BV(TOIE1) );
}

void enable_timer1_interrupt(void){
	//sei();
	BIT_SET( TIMSK1, _BV(TOIE1) );
}
