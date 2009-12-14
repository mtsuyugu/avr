#ifndef TIMER_H
#define TIMER_H

#include "common.h"

/* 2msec timer */
void periodic_timer_init(void);
void periodic_timer_reset(void);
void periodic_timer_start(void);
void periodic_timer_stop(void);
#define priodic_timer_is_stopped() \
   ((TCCR2 & (_BV(CS21) | _BV(CS20))) == 0)


#endif /* TIMER_H */
