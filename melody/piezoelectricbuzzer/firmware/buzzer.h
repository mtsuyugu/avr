#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include "macro.h"

void buzzer_init(void);
void set_buzzer_output(uint8_t onoff );
// called in ISR, this is defined as macro
#define buzzer_toggle() (tbi(PORTD,_BV(PORTD6)));


#endif /* BUZZER_H */
