/* Name: main.c
 * Author: Masaaki Tsuyuguchi a.k.a @mtsuyugu
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "switch.h"
#include "led.h"
#include "buzzer.h"
#include "table.h"
#include "sound_ctlr.h"

/* F_CPU defined in Makefile
#define F_CPU 1000000
*/

// configuration
#define BPM 180
#define SCORE SCORE_DAISYBELL

int main(void) {

   /* H/W initialize */
   uint8_t playing = 0;
   pitch_timer_init();
   note_timer_init();
   sw_init();
   led_init();
   buzzer_init();

   sei();

   /* S/W initialize */
   uint8_t *table = get_score(SCORE);
   sound_ctlr_init( table, BPM );
   led_set(1);

   /* main loop */
   while(1){
      if( playing && is_note_end() ){
         if( is_score_end() ){
            // 曲の最後まで鳴らし終わった
            set_buzzer_output(0);
            sound_reset_position();
            playing = 0;
         }
         else{
            // 次の音符をならす
            sound_next();
         }
         continue;
      }
      if( sw_get() == SW_ON ){
         periodic_timer_reset();
         playing ^= 1;
         if( playing ){
            if( sound_get_position() != 0 ){
               // 曲の途中で止まっていたのが再開されたとき
               sound_start();
            }
         }
         else{
            // 再生中の曲を止める
            sound_stop();
            set_buzzer_output(0);
         }
         continue;
      }
   }

   return 0;   /* never reached */
}
