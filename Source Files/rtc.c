#include <LPC21xx.H>
#include <stdio.h>
#include "rtc_defines.h"
#include "types.h"
#include "lcd.h"
#include "rtc.h"
#include "uart.h"
#include "delay.h"
#include "dot_matrix.h"
#include "uart_interrupt.h"

extern u8 r_flag,f;
char  timestr[100];
s32 hour,min,sec,date,month,year,day;

char *days[]={"SUNDAY","MONDAY","TUEDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};


// Array to hold names of days of the week
char week[][10] = {"SUNDAY","MONDAY","TUEDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};


/*
Initialize the Real-Time Clock (RTC)
This function disables the RTC, sets the prescaler values, 
and then enables the RTC.
*/
void RTC_Init(void) 
{
  // Disable and reset the RTC
	CCR = RTC_RESET;
	
  
#ifdef _LPC2148
  // Enable the RTC & select the clock source
	CCR = RTC_ENABLE | RTC_CLKSRC;  
#else
  // Set prescaler integer and fractional parts
	PREINT = PREINT_VAL;
	PREFRAC= PREFRAC_VAL;
  
  // Enable the RTC
	CCR = RTC_ENABLE;  
	
#endif

}
void setrtc(void)
{
	SetRTCTimeInfo(12,14,00);
	SetRTCDateInfo(30,10,2025);
	SetRTCDay(4);
}

/*
Get the current RTC time
hour Pointer to store the current hour
minute Pointer to store the current minute
second Pointer to store the current second
*/
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

/*
Display the RTC time on LCD
hour value (0 23)
minute value (0 59)
second value (0 59) seperated by ':'
*/



//void DisplayRTCTime(u32 hour, u32 minute, u32 second)
//{
//		CmdLCD(0x80);
//		CharLCD((hour/10)+48);
//		CharLCD((hour%10)+48);
//		CharLCD(':');
//		CharLCD((minute/10)+48);
//		CharLCD((minute%10)+48);
//		CharLCD(':');
//		CharLCD((second/10)+48);
//		CharLCD((second%10)+48);

//}

/*
Get the current RTC date
day Pointer to store the current date (1 31)
month Pointer to store the current month (1 12)
year Pointer to store the current year (four digits)
*/
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

/*
Display the RTC date on LCD
Day of month (1 31)
Month (1 12)
Year (four digits) and seperated by '/'
*/
//void DisplayRTCDate(u32 date, u32 month, u32 year)
//{
//		CmdLCD(0xC0);
//		CharLCD((date/10)+48);
//		CharLCD((date%10)+48);
//		CharLCD('/');
//		CharLCD((month/10)+48);
//		CharLCD((month%10)+48);
//		CharLCD('/');
//		//U32LCD(year);
//}

/*
Set the RTC time
Hour to set (0 23)
Minute to set (0 59)
Second to set (0 59)
*/
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)
{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}

/*
Set the RTC date
day of month to set (1 31)
month to set (1 12)
year to set (four digits)
*/
void SetRTCDateInfo(u32 date, u32 month, u32 year)
{
	DOM = date;
	MONTH = month;
	YEAR = year;	
}

/*
Get the current day of the week
dow Pointer to store Day of Week (0=Sunday, ..., 6=Saturday)
*/
void GetRTCDay(s32 *day)
{
	*day = DOW; 
}

/*
Display the current day of the week on LCD
dow (Day of Week) (0=Sunday, ..., 6=Saturday)
*/
//void DisplayRTCDay(u32 dow)
//{
//	CmdLCD(0x8A);
//	StrLCD(week[dow]);  
//}

/*
Set the day of the week in RTC
Day of Week to set (0=Sunday, ..., 6=Saturday)
*/
void SetRTCDay(u32 day)
{
	DOW = day;
}

void display_m_s()
{

// Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		//DisplayRTCTime(hour,min,sec);
	//	GetRTCDateInfo(&date,&month,&year);
		//DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		//DisplayRTCDay(day);
		

     Displaytime(min,sec,130);
}

void display_rtc()
{
	char timestr[100];
//	u8 *p;
	// Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		//DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		//DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		//DisplayRTCDay(day);
	
     //Displaytime(min,sec);
		sprintf(timestr,
		"   TIME:%02d:%02d:%02d DATE:%02d/%02d/%02d DAY:%s    ",
		hour,min,sec,date,month,year,days[day]);
//		p=(u8 *)timestr;
//		len=0;
//		while(*p)
//		{
//			len++;
//		}	 
////		UART0_TxString(timestr);
//		delay_s(1);
//		for(i=0;i<len-3;i++)
//		{
//			display_str(&timestr[i],100);
//		}						  
		scrolling_rtc(timestr); 
		if(r_flag==1)
		 {
		 //	index_val=0;
			r_flag=0;
			return;
		 }  
}
