#include <stddef.h>
#include "timer.h"
#include "buzzer.h"
#include "sound_ctlr.h"
#include "table.h"

static uint16_t score_idx = 0;
static uint8_t *score_table = NULL;
static uint16_t bpm = 100;
static uint8_t pitch;
static uint8_t note;


// F_CPU = 10^6
// value = F_CPU/(2*pitch)-1
static uint16_t pitch_table[] = {
1910, // C 261.626Hz
1802,
1701, // D
1606,
1515, // E
1430, // F
1350,
1274, // G
1202,
1135, // A 440Hz
1071,
1011, // B
 954, // CH
 900,
 850, // DH
 802,
 757, // EH
 714, // FH
 674,
 636 // GH
};

void sound_stop( void ){
   note_timer_stop();
   pitch_timer_stop();
}

void sound_start(void){
   if( pitch != RST ){
      pitch_timer_start();
   }
   note_timer_start();
}

void sound_lookup(void){
   pitch = score_table[score_idx];
   note = score_table[score_idx+1];
}

void sound_set(void){
   uint16_t pitch_count;
   if( pitch != RST ){
      pitch_count = pitch_table[ pitch ];
      pitch_timer_set_counter(pitch_count);
   }
   else{
      set_buzzer_output(0);
   }
   uint16_t note_duration = 100 * note / 16 * 60 / bpm;
   note_timer_set_counter(note_duration); 
}

void sound_next(void){
   sound_lookup();
   sound_set();
   sound_start();
}

uint8_t is_score_end(void){
   return score_table[score_idx] == END;
}

void sound_ctlr_init(uint8_t *_score_table, uint16_t _bpm){
   score_table = _score_table;
   bpm = _bpm;
}

void sound_reset_position(void){
   score_idx = 0;
}

uint16_t sound_get_position(void){
   return score_idx;
}

void sound_increment(void){
   score_idx += NOTE_UNIT;
}

