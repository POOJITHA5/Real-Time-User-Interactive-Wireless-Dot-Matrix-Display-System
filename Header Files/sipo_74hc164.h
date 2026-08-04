#ifndef SIPO_74HC164_H
#define SIPO_74HC164_H

#include "types.h"
#define DM1 1
#define DM2 2
#define DM3 3 
#define DM4 4

void Init_SIPO(void);
void SIPO_74HC164_1(u8);
void SIPO_74HC164_2(u8);
void SIPO_74HC164_3(u8);
void SIPO_74HC164_4(u8);

#endif
