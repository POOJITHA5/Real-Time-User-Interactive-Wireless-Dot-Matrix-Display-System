#include <LPC21xx.h>

#include "types.h"
#include "defines.h"
#include "adc_defines.h"
#include "delay.h"
#include "dot_matrix.h"

#define ADC_FUNC 0x01 
extern u8 r_flag;
u32 adcChSel[4]={AIN0_PIN_0_27,
                 AIN1_PIN_0_28,
                 AIN2_PIN_0_29,

		 AIN3_PIN_0_30
                };

void Init_ADC(u32 chNo)
{
	//clear prev cfgs of p0.27-p0.30
	PINSEL1&=~(adcChSel[chNo]);
	//cfg req p0.27-p0.30 as AIN0-AIN3 pins
	PINSEL1|=adcChSel[chNo];
	//cfg ADCR
	ADCR|=(1<<PDN_BIT)|(CLKDIV<<CLKDIV_BITS);
}

void Read_ADC(u32 chNo,f32 *eAR,u32 *adcDVal)
{
	//clear any previous channel selection
	ADCR&=0xFFFFFF00;
	//update req chNo,& start conv
	ADCR|=((1<<ADC_CONV_START_BIT)|(1<<chNo));
	//wait for conv time
	delay_us(3);
	//check if conv completed successfully
	while(((ADDR>>DONE_BIT)&1)==0);
	//stop adc conversion
	ADCR&=~(1<<ADC_CONV_START_BIT);
	//read digital data
	*adcDVal=((ADDR>>DIGITAL_DATA_BITS)&1023);
	
	*eAR=(*adcDVal )* (3.3/1023);
}

void lm35()
{
       	f32 eAR;
		u32 adcDVal;

        Read_ADC(CH1,&eAR,&adcDVal);

        Displaytemperature(eAR*100,500);
		if(r_flag==1)
		 {
			r_flag=0;
			return;
		 }

       // delay_ms(1000);
}
