#include "adc_controller.h"
#include "led.h"
#include "adc.h"

#define is_adc_on() (adc_on == 1)

static uint8_t adc_on = 0;

void adc_controller_handle_switch( void ){
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
}

uint8_t adc_controller_start_conversion(){
   if( is_adc_on() && !is_adc_in_conversion() ){
      adc_start(NEXT_AXIS);
      return 1;
   }
   return 0;
}

