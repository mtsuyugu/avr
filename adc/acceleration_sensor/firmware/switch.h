#ifndef SWITCH_H
#define SWITCH_H

#include "common.h"

// physical level
#define SW_PH_ON 0  // active low
#define SW_PH_OFF 1

#define SW_COUNT_MAX 15


void sw_init();
uint8_t sw_get();
void sw_check_port(void);
#define sw_get_port() (PIND & _BV(PIND2))
extern volatile uint8_t sw_count;
extern volatile uint8_t sw_now;

#endif /* SWITCH_H */
