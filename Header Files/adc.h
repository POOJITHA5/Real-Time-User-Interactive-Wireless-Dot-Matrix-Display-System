#ifndef _ADC_H_
#define _ADC_H_

#include "types.h"
void Init_ADC(u32);
void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal);
//void Displaytemperature(u32,u32);
void lm35(void);


#endif
