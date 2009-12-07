#include <avr/io.h>
#include <avr/interrupt.h>

void buzzer_init(void){
   DDRD |= _BV(DDD5);
}

void set_buzzer_output(uint8_t onoff ){
   if( onoff ){
      PORTD |= _BV(PORTD5);
   }
   else{
      PORTD &= ~_BV(PORTD5);
   }
}

