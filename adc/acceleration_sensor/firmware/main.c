/* Name: main.c
 * Author: Masaaki Tsuyuguchi a.k.a @mtsuyugu
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "timer.h"
#include "switch.h"
#include "lcd.h"
#include "led.h"
#include "macro.h"

/* F_CPU defined in Makefile
#define F_CPU 1000000
*/

// configuration
#define BPM 180
#define SCORE SCORE_DAISYBELL
#define JTAGDISABLED

int main(void) {

   /* H/W initialize */
   disable_jtag();
   periodic_timer_init();
   adc_init();
   sw_init();
   lcd_init();
   led_init();

   /* S/W initialize */
   lcd_position(0,0);
   lcd_put_str("X    Y    Z");
   led_set(1);
   static uint8_t adc_on = 0;
   sei();

   /* main loop */
   while(1){
      uint8_t sw_status = sw_get();
      switch( sw_status ){
      case SW_ON:
         // switch ON
         adc_on ^= 1;
         if( adc_on ){
            led_set(1);
            adc_start(NEXT_AXIS);
         }
         else{
            led_set(0);
            adc_stop();
         }
         continue;
      case SW_OFF:
         break;
      case SW_ON_CONT:
         break;
      case SW_OFF_CONT:
         break;
      default:
         break; /* never reached */
      }
      if( lcd_has_data_to_display() ){
         lcd_display();
         continue;
      }
      if( adc_on && (ADCSRA & _BV(ADSC)) == 0 ){
         adc_start(NEXT_AXIS);
         continue;
      }
   }

   return 0;   /* never reached */
}
