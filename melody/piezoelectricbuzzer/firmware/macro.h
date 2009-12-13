#ifndef MACRO_H
#define MACRO_H

#define sbi(port, bit) ((port) |= (bit))
#define cbi(port, bit) ((port) &= ~(bit))
#define tbi(port, bit) ((port) ^= (bit))

#define jtag_disabled() \
   (MCUCSR |= _BV(JTD);) \
   (MCUCSR |= _BV(JTD);) 

#endif /* MACRO_H */
