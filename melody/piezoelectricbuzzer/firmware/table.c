#include <stddef.h>
#include "table.h"


static uint8_t score_doremi[] = {
   C,n4, D,n8, E,n4, F,n8, G,n4, A,n8, B,n4, CH,n4, END
};

static uint8_t score_daisybell[] = {
//   D,n4, Cs,n4, D,n4, B,n4, A,n4, G,n4, A,n2, Fs,n4, D,n1, A,n1, D,n1, DH,n1, B,n2, RST,n4, DH,n4, CHs,n4, DH,n4,
//   B,n4, A,n4, G,n4, A,n2, Fs,n4, D,n1, G,n4, D,n4, G,n4, Fs,n4, D,n4, A,n4, G,n12, RST,n4, B,n4, CH,n4, B,n4,
//   A,n4, G,n4, Fs,n4, B,n2, G,n4, E,n1, DH,n4, CH,n4, B,n4, A,n2, As,n4, B,n12, RST,n4, B,n4, CH,n4, B,n4,
//   A,n4, G,n4, Fs,n4, B,n2, G,n4, E,n2, B,n4, A,n4, EH,n4, CHs,n4, B,n2, A,n4, DH,n12, RST,n4, 
   DH,n1, B,n1, G,n1,
   D,n1, E,n4, Fs,n4, G,n4, E,n2, G,n4, D,n12, RST,n4, A,n1, DH,n1, B,n1, G,n1, E,n4, Fs,n4, G,n4, A,n2, B,n4,
   A,n14, RST,n4, B,n4, CH,n4, B,n4, A,n4, DH,n2, B,n4, A,n4, G,n0, A,n4, B,n2, G,n4, E,n2, G,n4, E,n4, D,n1,
   RST,n4, D,n4, G,n2, B,n4, A,n2, RST,n4, G,n2, B,n4, A,n4, B,n4, CH,n4, DH,n4, B,n4, G,n4, A,n2, D,n4, G,n12,
   END
};

static uint8_t score_doremi2[] = {
   C,n4, D,n4, C,n4, C,n4, END
};

static uint8_t *score_table[] = {
   score_doremi,
   score_daisybell,
   score_doremi2,
};

uint8_t *get_score( uint16_t id ){
   if( id >= SCORE_NUM ){
      return NULL;
   }
   return score_table[id];
}
