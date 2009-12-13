#include <stdint.h>
#include <avr/io.h>
#include "macro.h"
#include "switch.h"
#include "timer.h"

#define SW_COUNT_MAX 15

volatile uint8_t sw_count = 0;
volatile uint8_t sw_next_state = SW_ON;
volatile uint8_t sw_now = SW_PH_ON;

/**
 * PD2(INT0) is input and pulled up.
 * INT0 is both edge triggered
 */
void sw_init(){
   cbi(DDRD, _BV(DDD2));
   sbi(PORTD, _BV(PORTD2));
   sbi(MCUCR, _BV(ISC00));
   cbi(MCUCR, _BV(ISC01));
   sbi(GICR, _BV(INT0));  // INT0 interrupt enabled
}

uint8_t sw_get(){
   static uint8_t confirmed = SW_OFF;
   if( sw_count >= SW_COUNT_MAX ){
      periodic_timer_stop();
      sw_count = 0;
      confirmed = (sw_now == SW_PH_ON) ? SW_ON : SW_OFF;
      return confirmed;
   }
   return (confirmed == SW_ON) ? SW_ON_CONT : SW_OFF_CONT;
}


