#include <stdint.h>
#include <avr/io.h>
#include "switch.h"
#include "timer.h"

#define SW_COUNT_MAX 15
#define SW_PH_ON 0  // active low
#define SW_PH_OFF 1
#define sw_get_port() (PINA & _BV(PINA0))

volatile static uint8_t sw_on_count = 0;
volatile static uint8_t sw_next_state = SW_ON;
volatile static uint8_t sw_now_expected = SW_PH_ON;

void sw_init(){
   DDRA &= ~_BV(DDA0);
   PORTA |= _BV(PORTA0);
}

uint8_t sw_get(){
   if( sw_on_count == SW_COUNT_MAX ){
      sw_on_count = 0;
      uint8_t confirmed = sw_next_state;
      sw_next_state ^= 1;
      sw_now_expected ^= 1;
      return confirmed;
   }
   if( sw_on_count == 0 && sw_get_port() == sw_now_expected ){
      // periodic state check start
      sw_on_count = 1;
      periodic_timer_reset();
      periodic_timer_start();
   }
   else{
      // state of port is checked in ISR
      //  or already state confirmed
   }
   return SW_OFF;
}

/**
 * port check function
 *  - called from ISR
 *  - if port is logical on, increment count
 *  - else, counter reset
 */
void sw_check_port(void){
   if( sw_get_port() != sw_now_expected ){
      sw_on_count = 0;
      periodic_timer_stop();
   }
   else if( ++sw_on_count == SW_COUNT_MAX ){
      // switch-on confirmed
      periodic_timer_stop();
   }
   else{
      // continue state check
   }
}

