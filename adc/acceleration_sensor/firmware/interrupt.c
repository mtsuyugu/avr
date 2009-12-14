#include <avr/interrupt.h>
#include "adc.h"
#include "lcd.h"
#include "led.h"
#include "switch.h"
#include "timer.h"

ISR(TIMER2_COMP_vect){
   if( ++sw_count >= SW_COUNT_MAX ){
      periodic_timer_stop();
   }
}

ISR(INT0_vect){
   sw_now = sw_get_port();
   periodic_timer_stop();
   periodic_timer_reset();
   periodic_timer_start();
}

ISR(ADC_vect){
   uint16_t value = adc_get_raw_value();
   lcd_set_hex16( value, LCD_LOWER, now_in_measure*5 );
}

