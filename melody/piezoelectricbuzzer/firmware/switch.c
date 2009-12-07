#include <stdint.h>
#include <avr/io.h>
#include "switch.h"

#define SW_PH_ON 0  // active low
#define SW_PH_OFF 1

void sw_init(){
   DDRA &= ~_BV(DDA0);
   PORTA |= _BV(PORTA0);
}

uint8_t sw_get(){
#define SW_COUNT 8
   static uint8_t count = 0;
   if( (PINA & _BV(PINA0)) == SW_PH_ON ){
      if( count >= SW_COUNT || ++count == SW_COUNT ){
         return SW_ON;
      }
   }
   else{
      count = 0;
   }
   return SW_OFF;
}
