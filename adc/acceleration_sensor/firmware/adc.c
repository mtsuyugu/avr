#include "macro.h"
#include "adc.h"

uint8_t now_in_measure = 0xff;
static uint16_t value[AXIS_MAX+1];

void adc_init(){
   // If other than 1MHz is used as system clock, it shall be changed.
   uint8_t clock = _BV(ADPS0)|_BV(ADPS1); // 1/8 clk
   sbi(ADCSRA, _BV(ADEN)|_BV(ADIE)|clock);
}

void adc_start(uint8_t i){
   if( i > AXIS_MAX ){
      ++now_in_measure;
      if(now_in_measure > AXIS_MAX){
         now_in_measure = XAXIS;
      }
   }
   else{ 
      now_in_measure = 0x03 & i;
   }
   ADMUX = now_in_measure; // port 
   // adc clk on, adc stat, adc complete interrupt enabled
   sbi(ADCSRA, _BV(ADEN)|_BV(ADIE)|_BV(ADSC));
}

void adc_stop(void){
   // adc clk off, adc complete intterrupt disabled
   cbi(ADCSRA, _BV(ADEN)|_BV(ADIE));
}

// called in ISR
uint16_t adc_get_raw_value(void){
   return value[now_in_measure] = ADC;
}

uint16_t adc_get_value(uint8_t i){
   if( i > AXIS_MAX ){
      return 0;
   }
   return value[i];
}

