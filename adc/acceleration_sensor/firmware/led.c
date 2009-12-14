#include "macro.h"
#include "led.h"

void led_init(){
   sbi(DDRD, _BV(DDD5));
}

void led_set( uint8_t onoff ){
   if( onoff ){
      sbi(PORTD, _BV(PORTD5));
   }
   else{
      cbi(PORTD, _BV(PORTD5));
   }
}

void led_toggle(){
   tbi(PORTD, _BV(PORTD5));
}
