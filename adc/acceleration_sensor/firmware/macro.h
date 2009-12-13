#ifndef MACRO_H
#define MACRO_H

#define sbi(port, bit) ((port) |= (bit))
#define cbi(port, bit) ((port) &= ~(bit))
#define tbi(port, bit) ((port) ^= (bit))

// To disable JTAG bit JTD is on twice to MCUCSR
#define disable_jtag() sbi(MCUCSR, _BV(JTD)); sbi(MCUCSR, _BV(JTD));


#endif /* MACRO_H */
