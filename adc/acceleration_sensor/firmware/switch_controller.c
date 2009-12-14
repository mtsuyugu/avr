#include "switch_controller.h"
#include "switch.h"

static void (*ftable[])(void) = {NULL, NULL, NULL, NULL};

void switch_controller_add_handler( uint8_t state, void (*handler)(void) ) {
   if( state >= SW_ON_CONT ){
      return;
   }
   ftable[state] = handler;
}

uint8_t switch_controller_main( void ){
   uint8_t sw_status = sw_get();
   if( ftable[sw_status] == NULL ){
      return 0;
   }
   ftable[sw_status]();
   return 1;
}
