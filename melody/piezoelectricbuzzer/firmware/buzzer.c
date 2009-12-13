#include <avr/io.h>
#include <avr/interrupt.h>
#include "macro.h"

void buzzer_init(void){
   sbi(DDRD, _BV(DDD6));
}

void set_buzzer_output(uint8_t onoff ){
   if( onoff ){
      sbi(PORTD, _BV(PORTD6));
   }
   else{
      cbi(PORTD, _BV(PORTD6));
   }
}

