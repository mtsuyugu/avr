#include <avr/io.h>
#include "macro.h"
#include "timer.h"

static uint16_t note_count = 0;
static uint16_t note_duration = 0; // duration = note_length*10msec

/**
 * 16bit-timer/counter1 initialize
 *  - CTC mode
 */
void pitch_timer_init(void){
   TCCR1B = _BV(WGM12);
}

/**
 * 16bit-timer/counter1 set compare value
 * 16bit-timer/counter1 clear counter
 */
void pitch_timer_set_counter(uint16_t count){
   OCR1A = count;
   TCNT1 = 0;
}

/**
 * 16bit-timer/counter1 interrupt enabled
 * 16bit-timer/counter1 start(prescale:none)
 */
void pitch_timer_start(void){
   sbi(TIMSK, _BV(OCIE1A));
   sbi(TCCR1B, _BV(CS10));
}

/**
 * 16bit-timer/counter1 stop
 * 16bit-timer/counter1 interrupt disabled
 */
void pitch_timer_stop(void){
   cbi(TCCR1B, _BV(CS10));
   cbi(TIMSK, _BV(OCIE1A));
}

/**
 * 8bit-timer/counter 0 initialize
 *  - set CTC mode
 */
void note_timer_init(void){
   sbi(TCCR0, _BV(WGM01));
}

/**
 * 8bit-timer/counter0 set compare value
 * 8bit-timer/counter0 clear counter
 */
void note_timer_set_counter(uint16_t count){
   note_count = 0;
   note_duration = count;
   OCR0 = 155; // 10msec (i.e. F_CPU/(prescale * 0.01) - 1)
   TCNT0 = 0;
}

void note_count_reset(void){
   note_count = 0;
}

uint8_t note_counter_increment(void){
   return ++note_count == note_duration; 
}

/**
 * 8bit-timer/counter0 interrupt enabled
 * 8bit-timer/counter0 start(prescale:1/64)
 */
void note_timer_start(){
   sbi(TIMSK, _BV(OCIE0));
   sbi(TCCR0, _BV(CS01) | _BV(CS00));
}

/**
 * 8bit-timer/counter1 stop
 * 8bit-timer/counter1 interrupt disabled
 */
void note_timer_stop(){
   cbi(TCCR0, _BV(CS01) | _BV(CS00));
   cbi(TIMSK, _BV(OCIE0));
}

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
