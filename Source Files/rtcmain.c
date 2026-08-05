#include <lpc214x.h>
#include <stdio.h>
#include "rtc.h"
#include "lcd.h"
#include "uart.h"
#include "delay.h"

s32 hour,min,sec,date,month,year,day;

char *days[]={"SUNDAY","MONDAY","TUEDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};

char timestr[60];

// Main function
int main()
{
  // Initialize RTC 
	RTC_Init();
	UART0_Init();
		
  // Initialize the LCD
	//InitLCD();
	
  // Set the initial time (hours, minutes, seconds)
//	SetRTCTimeInfo(12,14,00);
//	SetRTCDateInfo(30,10,2025);
//	SetRTCDay(4);
     setrtc();

  while (1) 
	{
    // Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		//DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		//DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		//DisplayRTCDay(day);
		
     Displaytime(min,sec,140);
		
		sprintf(timestr,
		"TIME:%02d:%02d:%02d DATE:%02d/%02d/%02d DAY:%s",
		hour,min,sec,date,month,year,days[day]);
		
		UART0_TxString(timestr);
		delay_s(1);
		//scroll_string(timestr); 
	}
}

