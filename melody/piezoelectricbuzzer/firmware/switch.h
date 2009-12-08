#ifndef SWITCH_H
#define SWITCH_H

#define SW_OFF 0
#define SW_ON 1

void sw_init();
uint8_t sw_get();
void sw_check_port(void);

#endif /* SWITCH_H */
