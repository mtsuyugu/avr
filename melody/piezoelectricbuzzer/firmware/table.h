#ifndef TABLE_H
#define TABLE_H

#include <stdint.h>

#define C    0
#define Cs   1
#define D    2
#define Ds   3
#define E    4
#define F    5
#define Fs   6
#define G    7
#define Gs   8
#define A    9
#define As  10
#define B   11
#define CH  12
#define CHs 13
#define DH  14
#define DHs 15
#define EH  16
#define FH  17
#define FHs 18
#define GH  19
#define RST 0xF0
#define END 0xFF

#define n16 4  // sixteenth note
#define n8  8  // eighth note
#define n6  12 // dotted eighth note
#define n4  16 // quarter note
#define n3  24 // dotted quarter note
#define n2  32 // half note
#define n1  48 // dotted half note
#define n0  64 // whole note

#define n12 80 // tied dotted half note and half note 
#define n14 64 // tied dotted half note and quarter note

#define NOTE_UNIT 2 // 2 byte/note 
#define SCORE_DOREMI 0
#define SCORE_DAISYBELL 1
#define SCORE_NUM 2

uint8_t *get_score( uint16_t id );

#endif /* TABLE_H */
