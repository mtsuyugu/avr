#include <avr/interrupt.h>
#include "led.h"
#include "switch.h"
#include "timer.h"
#include "table.h"
#include "sound_ctlr.h"

// 圧電ブザーを振動させる
ISR(TIMER1_COMPA_vect){
   PORTD ^= _BV(PORTD5);
}

// 決められた時間だけ鳴動したら次の音符へ
ISR(TIMER0_COMP_vect){
   if( note_counter_increment() ){
      note_count_reset(); // これはいらないかも
      led_toggle();
      sound_stop();
      sound_increment();
   }
}

ISR(TIMER2_COMP_vect){
   sw_check_port();
}
