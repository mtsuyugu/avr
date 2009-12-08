#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void pitch_timer_init(void);
void pitch_timer_set_counter(uint16_t count );
void pitch_timer_start(void);
void pitch_timer_stop(void);

#define note_timer_is_stopped() \
   ((TCCR0 & (_BV(CS01) | _BV(CS00))) == 0)

void note_timer_init(void);
void note_timer_set_counter(uint16_t count);
void note_count_reset(void);
uint8_t note_counter_increment(void);
void note_timer_start(void);
void note_timer_stop(void);

/* 10msec timer */
void periodic_timer_init(void);
void periodic_timer_reset(void);
void periodic_timer_start(void);
void periodic_timer_stop(void);
#define priodic_timer_is_stopped() \
   ((TCCR2 & (_BV(CS21) | _BV(CS20))) == 0)


#endif /* TIMER_H */
