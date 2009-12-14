/* Name: main.c
 * Author: Masaaki Tsuyuguchi a.k.a @mtsuyugu
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/interrupt.h>

#include "common.h"
#include "macro.h"
#include "timer.h"
#include "switch.h"
#include "adc.h"
#include "lcd.h"
#include "led.h"
#include "switch_controller.h"
#include "adc_controller.h"

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
   switch_controller_add_handler( SW_ON, adc_controller_handle_switch );

   sei();

   /* main loop */
   while(1){
      if( switch_controller_main() ){
         continue;
      }
      if( lcd_has_data_to_display() ){
         lcd_display();
         continue;
      }
      if( adc_controller_start_conversion() ){
         continue;
      }
   }

   return 0;   /* never reached */
}
