#include <avr/io.h>
#include "macro.h"
#include "timer.h"

/**
 * 8bit-timer/counter 2 initialize
 *  - set CTC mode
 */
void periodic_timer_init(void){
   sbi(TCCR2, _BV(WGM21));
}

/**
 * 8bit-timer/counter 2 reset
 *  - reset timer/counter 2
 */
void periodic_timer_reset(void){
   OCR2 = 250; /* 2msec */
   TCNT2 = 0;
}

/**
 * 8bit-timer/counter 2 interrupt enabled
 * 8bit-timer/counter 2 start(prescale:1/8)
 */
void periodic_timer_start(void){
   sbi(TIMSK, _BV(OCIE2));
   sbi(TCCR2, _BV(CS21));
}

/**
 * 8bit-timer/counter 2 stop
 * 8bit-timer/counter 2 interrupt disabled
 */
void periodic_timer_stop(void){
   cbi(TCCR2, _BV(CS21));
   cbi(TIMSK, _BV(OCIE2));
}
