#ifndef SW_CTRLER_H
#define SW_CTRLER_H

#include "common.h"

// logical state
#define SW_OFF 0
#define SW_ON 1
#define SW_OFF_CONT 2
#define SW_ON_CONT 3

void switch_controller_add_handler( uint8_t state, void (*handler)(void) );
uint8_t switch_controller_main( void );

#endif /* SW_CTRLER_H */
