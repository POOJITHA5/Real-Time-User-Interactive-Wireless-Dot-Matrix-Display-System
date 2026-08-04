#ifndef RTC_H
#define RTC_H

#include "types.h"

void RTC_Init(void);
void GetRTCTimeInfo(s32 *,s32 *,s32 *);
void DisplayRTCTime(u32,u32,u32);
void GetRTCDateInfo(s32 *,s32 *,s32 *);
void DisplayRTCDate(u32,u32,u32);

void SetRTCTimeInfo(u32,u32,u32);
void SetRTCDateInfo(u32,u32,u32);

void GetRTCDay(s32 *);
void DisplayRTCDay(u32);
void SetRTCDay(u32);

void Displaytime(u32,u32,u32);
void setrtc(void);
//void scroll_string(char *); 
void display_rtc(void);
void display_m_s(void);


#endif
