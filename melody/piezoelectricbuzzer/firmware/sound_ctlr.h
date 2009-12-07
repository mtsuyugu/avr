#ifndef SOUND_CTLR_H
#define SOUND_CTLR_H

#include <stdint.h>

#define is_note_end note_timer_is_stopped
void sound_stop(void);
void sound_start(void);
void sound_lookup(void);
void sound_set(void);
void sound_next(void);
uint8_t is_score_end(void);
void sound_ctlr_init(uint8_t *sound_table, uint16_t bpm);
void sound_reset_position(void);
uint16_t sound_get_position(void);
void sound_increment(void);

#endif /* SOUND_CTLR_H */
