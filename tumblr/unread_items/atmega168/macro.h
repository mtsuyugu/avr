#ifndef MACRO_H
#define MACRO_H

#define BIT_CLEAR( ADDR, MASK) \
	((ADDR) &= ~(MASK))

#define BIT_SET( ADDR, MASK ) \
	((ADDR) |= (MASK))

#define BIT_TOGGLE( ADDR, MASK ) \
	((ADDR) ^= (MASK))

//#define F_CPU 20000000UL // 20MHz
#define F_CPU    8000000UL // 8MHz

#endif /* MACRO_H */
