#include <avr/io.h>
#include "led.h"

void led_init(){
   DDRC |= _BV(DDC0);
}

void led_set( uint8_t onoff ){
   if( onoff ){
      PORTC |= _BV(PORTC0);
   }
   else{
      PORTC &= ~_BV(PORTC0);
   }
}

void led_toggle(){
   PORTC ^= _BV(PORTC0);
}
