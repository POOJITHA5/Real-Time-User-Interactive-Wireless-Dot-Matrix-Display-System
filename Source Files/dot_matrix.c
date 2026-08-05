include <LPC21xx.H>
#include <stdio.h>
#include "defines.h"
#include "types.h"
#include "delay.h"
#include "sipo_74hc164.h"
#include "spi_eeprom.h "
#include "rtc.h"
#include "uart_interrupt.h"
#include <string.h>
#include <stdlib.h>
#define MAX 128
u8 *clr;
extern u8 index_val,new_var,ch,t_flag,r_flag,rec_buff[100],updated_str[100];
extern u8 f;
//extern u8 tx_index;
//extern u8 rx_buf[MAX];
//extern u8 rx_data;
//extern u32 flag;
extern s32 hour,min,sec,date,month,year,day;
char *buffer;
//#include "fixed_string.h"

u8 fbuff[10];
u8 sbuff[50];
u32 size;

unsigned char degree[8] =
{
0xE3,
0xDD,
0xDD,
0xE3,
0xFF,
0xFF,
0xFF,
0xFF
};

//dot matrix anodes connected to P0.0to P0.7
#define ROWS 16

/** fonts array **/
unsigned char font[96][8]={ 
{0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff},//space
{0xe7 ,0xc3 ,0xc3 ,0xe7 ,0xe7 ,0xff ,0xe7 ,0xff },//'!'
{0x99 ,0x99 ,0x99 ,0xff ,0xff ,0xff ,0xff ,0xff },//'"'
{0xc9 ,0xc9 ,0x80 ,0xc9 ,0x80 ,0xc9 ,0xc9 ,0xff },//'#'
{0xf7 ,0xc1 ,0xf5 ,0xc1 ,0xd7 ,0xc1 ,0xf7 ,0xff },//'$'
{0xff ,0x9c ,0xcc ,0xe7 ,0xf3 ,0x99 ,0x9c ,0xff },//'%'
{0xe3 ,0xc9 ,0xe3 ,0x91 ,0xc4 ,0xcc ,0x91 ,0xff },//'&'
{0xe7 ,0xe7 ,0xf3 ,0xff ,0xff ,0xff ,0xff ,0xff },//'''
{0xcf ,0xe7 ,0xf3 ,0xf3 ,0xf3 ,0xe7 ,0xcf ,0xff },//'('
{0xf3 ,0xe7 ,0xcf ,0xcf ,0xcf ,0xe7 ,0xf3 ,0xff },//')'
{0xff ,0x99 ,0xc3 ,0x80 ,0xc3 ,0x99 ,0xff ,0xff },//'*'
{0xff ,0xe7 ,0xe7 ,0x81 ,0xe7 ,0xe7 ,0xff ,0xff },//'+'
{0xff ,0xff ,0xff ,0xff ,0xe7 ,0xe7 ,0xf3 ,0xff },//','
{0xff ,0xff ,0xff ,0x80 ,0xff ,0xff ,0xff ,0xff },//'-'
{0xff ,0xff ,0xff ,0xff ,0xff ,0xf3 ,0xf3 ,0xff },//'.'
{0x9f ,0xcf ,0xe7 ,0xf3 ,0xf9 ,0xfc ,0xfe ,0xff },//'/'
{0xc1 ,0x9c ,0x8c ,0x84 ,0x90 ,0x98 ,0xc1 ,0xff },//'0'
{0xe7 ,0xe3 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0x81 ,0xff },//'1'
{0xc3 ,0x99 ,0x9f ,0xc7 ,0xf3 ,0x99 ,0x81 ,0xff },//'2'
{0xc3 ,0x99 ,0x9f ,0xc7 ,0x9f ,0x99 ,0xc3 ,0xff },//'3'
{0xc7 ,0xc3 ,0xc9 ,0xcc ,0x80 ,0xcf ,0x87 ,0xff },//'4'
{0x81 ,0xf9 ,0xc1 ,0x9f ,0x9f ,0x99 ,0xc3 ,0xff },//'5'
{0xc7 ,0xf3 ,0xf9 ,0xc1 ,0x99 ,0x99 ,0xc3 ,0xff },//'6'
{0x81 ,0x99 ,0x9f ,0xcf ,0xe7 ,0xe7 ,0xe7 ,0xff },//'7'
{0xc3 ,0x99 ,0x99 ,0xc3 ,0x99 ,0x99 ,0xc3 ,0xff },//'8'
{0xc3 ,0x99 ,0x99 ,0x83 ,0x9f ,0xcf ,0xe3 ,0xff },//'9'
{0xff ,0xf3 ,0xf3 ,0xff ,0xff ,0xf3 ,0xf3 ,0xff },//':'
{0xf3 ,0xf3 ,0xff ,0xff ,0xf3 ,0xf3 ,0xf9 ,0xff },//';'
{0xe7 ,0xf3 ,0xf9 ,0xfc ,0xf9 ,0xf3 ,0xe7 ,0xff },//'<'
{0xff ,0xff ,0x80 ,0xff ,0xff ,0x80 ,0xff ,0xff },//'='
{0xf9 ,0xf3 ,0xe7 ,0xcf ,0xe7 ,0xf3 ,0xf9 ,0xff },//'>'
{0xe1 ,0xcc ,0xcf ,0xe7 ,0xf3 ,0xff ,0xf3 ,0xff },//'?'
{0xc1 ,0x9c ,0x84 ,0x84 ,0x84 ,0xfc ,0xe1 ,0xff },//'@'
{0xe7 ,0xc3 ,0x99 ,0x99 ,0x81 ,0x99 ,0x99 ,0xff },//'A'
{0xc0 ,0x99 ,0x99 ,0xc1 ,0x99 ,0x99 ,0xc0 ,0xff },//'B'
{0xc3 ,0x99 ,0xfc ,0xfc ,0xfc ,0x99 ,0xc3 ,0xff },//'C'
{0xe0 ,0xc9 ,0x99 ,0x99 ,0x99 ,0xc9 ,0xe0 ,0xff },//'D'
{0x80 ,0xb9 ,0xe9 ,0xe1 ,0xe9 ,0xb9 ,0x80 ,0xff },//'E'
{0x80 ,0xb9 ,0xe9 ,0xe1 ,0xe9 ,0xf9 ,0xf0 ,0xff },//'F'
{0xc3 ,0x99 ,0xfc ,0xfc ,0x8c ,0x99 ,0x81 ,0xff },//'G'
{0x99 ,0x99 ,0x99 ,0x81 ,0x99 ,0x99 ,0x99 ,0xff },//'H'
{0xc3 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0xc3 ,0xff },//'I'
{0x87 ,0xcf ,0xcf ,0xcf ,0xcc ,0xcc ,0xe1 ,0xff },//'J'
{0x98 ,0x99 ,0xc9 ,0xe1 ,0xc9 ,0x99 ,0x98 ,0xff },//'K'
{0xf0 ,0xf9 ,0xf9 ,0xf9 ,0xb9 ,0x99 ,0x80 ,0xff },//'L'
{0x9c ,0x88 ,0x80 ,0x80 ,0x94 ,0x9c ,0x9c ,0xff },//'M'
{0x9c ,0x98 ,0x90 ,0x84 ,0x8c ,0x9c ,0x9c ,0xff },//'N'
{0xe3 ,0xc9 ,0x9c ,0x9c ,0x9c ,0xc9 ,0xe3 ,0xff },//'O'
{0xc0 ,0x99 ,0x99 ,0xc1 ,0xf9 ,0xf9 ,0xf0 ,0xff },//'P'
{0xc3 ,0x99 ,0x99 ,0x99 ,0x89 ,0xc3 ,0x8f ,0xff },//'Q'
{0xc0 ,0x99 ,0x99 ,0xc1 ,0x89 ,0x99 ,0x98 ,0xff },//'R'
{0xc3 ,0x99 ,0xf1 ,0xe3 ,0x8f ,0x99 ,0xc3 ,0xff },//'S'
{0x81 ,0xa5 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0xc3 ,0xff },//'T'
{0x99 ,0x99 ,0x99 ,0x99 ,0x99 ,0x99 ,0xc3 ,0xff },//'U'
{0x99 ,0x99 ,0x99 ,0x99 ,0x99 ,0xc3 ,0xe7 ,0xff },//'V'
{0x9c ,0x9c ,0x9c ,0x94 ,0x80 ,0x88 ,0x9c ,0xff },//'W'
{0x9c ,0xc9 ,0xe3 ,0xf7 ,0xe3 ,0xc9 ,0x9c ,0xff },//'X'
{0x99 ,0x99 ,0x99 ,0xc3 ,0xe7 ,0xe7 ,0xc3 ,0xff },//'Y'
{0x80 ,0x9c ,0xce ,0xe7 ,0xb3 ,0x99 ,0x80 ,0xff },//'Z'
{0xe1 ,0xf9 ,0xf9 ,0xf9 ,0xf9 ,0xf9 ,0xe1 ,0xff },//'['
{0xfc ,0xf9 ,0xf3 ,0xe7 ,0xcf ,0x9f ,0xbf ,0xff },//'\'
{0xe1 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0xe7 ,0xe1 ,0xff },//']'
{0xf7 ,0xe3 ,0xc9 ,0x9c ,0xff ,0xff ,0xff ,0xff },//'^'
{0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff ,0x80 },//'_'
{0xf3 ,0xf3 ,0xe7 ,0xff ,0xff ,0xff ,0xff ,0xff },//'`'
{0xff ,0xff ,0xe1 ,0xcf ,0xc1 ,0xcc ,0x91 ,0xff },//'a'
{0xf8 ,0xf9 ,0xf9 ,0xc1 ,0x99 ,0x99 ,0xc4 ,0xff },//'b'
{0xff ,0xff ,0xe1 ,0xcc ,0xfc ,0xcc ,0xe1 ,0xff },//'c'
{0xc7 ,0xcf ,0xcf ,0xc1 ,0xcc ,0xcc ,0x91 ,0xff },//'d'
{0xff ,0xff ,0xe1 ,0xcc ,0xc0 ,0xfc ,0xe1 ,0xff },//'e'
{0xe3 ,0xc9 ,0xf9 ,0xf0 ,0xf9 ,0xf9 ,0xf0 ,0xff },//'f'
{0xff ,0xff ,0xe1 ,0xcc ,0xcc ,0xc0 ,0xcf ,0xe1 },//'g'
{0xf8 ,0xf9 ,0xc9 ,0x91 ,0x99 ,0x99 ,0x98 ,0xff },//'h'
{0xf3 ,0xff ,0xf1 ,0xf3 ,0xf3 ,0xf3 ,0xe1 ,0xff },//'i'
{0xcf ,0xff ,0xcf ,0xcf ,0xcf ,0xcc ,0xcc ,0xe1 },//'j'
{0xf8 ,0xf9 ,0x99 ,0xc9 ,0xe1 ,0xc9 ,0x98 ,0xff },//'k'
{0xf1 ,0xf3 ,0xf3 ,0xf3 ,0xf3 ,0xf3 ,0xe1 ,0xff },//'l'
{0xff ,0xff ,0xc9 ,0x80 ,0x80 ,0x94 ,0x9c ,0xff },//'m'
{0xff ,0xff ,0xe0 ,0xcc ,0xcc ,0xcc ,0xcc ,0xff },//'n'
{0xff ,0xff ,0xe1 ,0xcc ,0xcc ,0xcc ,0xe1 ,0xff },//'o'
{0xff ,0xff ,0xc1 ,0x99 ,0x99 ,0xc1 ,0xf9 ,0xf1 },//'p'
{0xff ,0xff ,0x91 ,0xcc ,0xcc ,0xc1 ,0xcf ,0x87 },//'q'
{0xff ,0xff ,0xc4 ,0x91 ,0x99 ,0xf9 ,0xf0 ,0xff },//'r'
{0xff ,0xff ,0xc1 ,0xfc ,0xe1 ,0xcf ,0xe0 ,0xff },//'s'
{0xf7 ,0xf3 ,0xc1 ,0xf3 ,0xf3 ,0xd3 ,0xe7 ,0xff },//'t'
{0xff ,0xff ,0xcc ,0xcc ,0xcc ,0xcc ,0x91 ,0xff },//'u'
{0xff ,0xff ,0xcc ,0xcc ,0xcc ,0xe1 ,0xf3 ,0xff },//'v'
{0xff ,0xff ,0x9c ,0x94 ,0x80 ,0x80 ,0xc9 ,0xff },//'w'
{0xff ,0xff ,0x9c ,0xc9 ,0xe3 ,0xc9 ,0x9c ,0xff },//'x'
{0xff ,0xff ,0xcc ,0xcc ,0xcc ,0xc0 ,0xcf ,0xe7 },//'y'
{0xff ,0xff ,0xc0 ,0xe6 ,0xf3 ,0xd9 ,0xc0 ,0xff },//'z'
{0xc7 ,0xf3 ,0xf3 ,0xf8 ,0xf3 ,0xf3 ,0xc7 ,0xff },//'{'
{0xe7 ,0xe7 ,0xe7 ,0xff ,0xe7 ,0xe7 ,0xe7 ,0xff },//'|'
{0xf8 ,0xf3 ,0xf3 ,0xc7 ,0xf3 ,0xf3 ,0xf8 ,0xff },//'}'
{0x91 ,0xc4 ,0xff ,0xff ,0xff ,0xff ,0xff ,0xff },//'~'
};
// Initialize dot matrix row pins as output
void Init_dotmatrix()
{
    WRITEBYTE(IODIR0, ROWS, 0xFF);   // Configure P0.16–P0.23 as outputs
}


void display_str(u8 *str, u32 delay)
{
    u8 i;
    u32 dly;

 
    for(dly = 0; dly < delay; dly++)
    {
        // Scan all 8 rows of the dot matrix
        for(i = 0; i < 8; i++)
        {
            WRITEBYTE(IOPIN0, ROWS, 0x00);      // Turn OFF all rows

            // Send row data to the four dot matrix displays
            SIPO_74HC164_1(font[str[0]-32][i]);
            SIPO_74HC164_2(font[str[1]-32][i]);
            SIPO_74HC164_3(font[str[2]-32][i]);
            SIPO_74HC164_4(font[str[3]-32][i]);

            WRITEBYTE(IOPIN0, ROWS, (1<<i));    // Enable the current row

            delay_ms(1);                        

            // Exit if a UART command is received
            if(r_flag == 1)
            {
                return;
            }
        }
    }
}


void scrolling_rtc(char *str)
{
    u8 i, j, k;

    // Move through the string one character at a time
    for(i = 0; str[i+3] != 0; i++)
    {
        // Control scrolling speed
        for(k = 0; k < 50; k++)
        {
            // Scan all rows
            for(j = 0; j < 8; j++)
            {
                WRITEBYTE(IOPIN0, ROWS, 0x00);      // Turn OFF all rows

                // Display four consecutive characters
                SIPO_74HC164_1(font[str[i]-32][j]);
                SIPO_74HC164_2(font[str[i+1]-32][j]);
                SIPO_74HC164_3(font[str[i+2]-32][j]);
                SIPO_74HC164_4(font[str[i+3]-32][j]);

                WRITEBYTE(IOPIN0, ROWS, (1<<j));    // Enable current row

                delay_ms(1);                       

                // Exit scrolling if interrupt flag is set
                if(r_flag == 1)
                {
                    return;
                }
            }
        }
    }
}

void Displaytime(u32 minute, u32 second, u32 delay)
{
    u8 i;
    u32 dly;

    // Refresh display for the specified time
    for(dly = 0; dly < delay; dly++)
    {
        // Scan all rows
        for(i = 0; i < 8; i++)
        {
            WRITEBYTE(IOPIN0, ROWS, 0x00);      // Turn OFF all rows

            // Display minute and second digits
            SIPO_74HC164_1(font[(minute/10)+'0'-32][i]);
            SIPO_74HC164_2(font[(minute%10)+'0'-32][i]);
            SIPO_74HC164_3(font[(second/10)+'0'-32][i]);
            SIPO_74HC164_4(font[(second%10)+'0'-32][i]);

            WRITEBYTE(IOPIN0, ROWS, (1<<i));    // Enable current row

            delay_ms(1);                        // Refresh delay
        }

}
void Displaytemperature(u32 temp, u32 delay)
{
    u8 i;
    u32 dly;


    for(dly = 0; dly < delay; dly++)
    {
        // Scan all rows
        for(i = 0; i < 8; i++)
        {
            WRITEBYTE(IOPIN0, ROWS, 0x00);      // Turn OFF all rows

            // Display temperature digits, degree symbol and 'C'
            SIPO_74HC164_1(font[((temp/10)+'0')-32][i]);
            SIPO_74HC164_2(font[((temp%10)+'0')-32][i]);
            SIPO_74HC164_3(degree[i]);
            SIPO_74HC164_4(font['C'-32][i]);

            WRITEBYTE(IOPIN0, ROWS, (1<<i));    // Enable current row

            // Exit if interrupt flag is set
            if(r_flag == 1)
            {
                return;
            }

            delay_ms(1);                        
        }
    }
}



void fixed_string()
{
    PageRead_25LC512(0x0002, fbuff, 4);    

    fbuff[4] = '\0';                       

    display_str(fbuff, 500);               

    // Exit if interrupt flag is set
    if(r_flag == 1)
    {
        r_flag = 0;
        f = 0;
        return;
    }
}


// Display a blinking string
void blinking_string()
{
    PageRead_25LC512(0x0002, fbuff, 4);    

    fbuff[4] = '\0';                       

    display_str(fbuff, 100);               

    display_str("    ", 100);              

    // Exit if interrupt flag is set
    if(r_flag == 1)
    {
        r_flag = 0;
        f = 0;
        return;
    }
}
void scrolling_string()
{
    // Pointer variable to access the string buffer stored in sbuff
    char *m = (char *)sbuff;

    // Variable used for string scrolling loop
    u8 i;

    // Variable to store length of the string
    int len;

    // Read user message string from external EEPROM starting from address 0x0008
    // Store maximum 30 bytes into sbuff buffer
    PageRead_25LC512(0x0008, sbuff, 30);

    // Calculate the length of received string
    len = strlen(m);

    // Remove the last character (usually EEPROM stored newline/end character)
    sbuff[len-1] = '\0';

    // Add three spaces at the end of string for smooth scrolling gap
    strcat(m, "   ");

    // Scroll the complete string character by character
    for(i=0; i<len-1; i++)
    {
        // Display string from current position on dot matrix display
        // Delay value 100 controls scrolling speed
        display_str(&(sbuff[i]), 100);

        // Check if any new command/data is received through UART
        if(r_flag == 1)
        {
            // Clear receive flag
            r_flag = 0;

            // Reset flag variable
            f = 0;

            // Exit scrolling function when new data is received
            return;
        }
    }
}
u8 menu2[] =
"\r\n------ TEXT EDIT MODE MENU ------\r\n"
"F. FIXED STRING\r\n"
"S. STRING WITH SCROLLING\r\n";

u8 str1[]="\r\nEnter The Fixed String\r\n";
u8 str2[]="\r\nEnter The Scrolling String\r\n";
void text_edit_mode()
{
    // Send text edit menu options through UART
    UART0_Str(menu2);

    // Reset UART receive buffer index
    index_val = 0;

    // Wait until user input is received through UART
    while(r_flag == 0);

    // Clear receive flag after receiving data
    r_flag = 0;

    // Small delay for UART data processing
    delay_ms(20);

    // Check the received command character
    switch(rec_buff[0])
    {
        // Case 'F' or 'f' is used for fixed display text update
        case 'F':
        case 'f':

            // Send message asking user to enter fixed text
            UART0_Str(str1);

            // Reset receive buffer index
            index_val = 0;

            // Wait for user text input
            while(r_flag == 0);

            // Clear receive flag after receiving text
            r_flag = 0;

            // Reset flag variable
            f = 0;

            // Delay for data processing
            delay_ms(20);

            // Store received fixed text into external EEPROM
            // EEPROM address 0x0002 is used for fixed text storage
            PageWrite_25LC512(0x0002, rec_buff);

            // Reset buffer index
            index_val = 0;

            break;


        // Case 'S' or 's' is used for scrolling text update
        case 'S':
        case 's':

            // Send message asking user to enter scrolling text
            UART0_Str(str2);

            // Reset receive buffer index
            index_val = 0;

            // Wait for user text input
            while(r_flag == 0);

            // Clear receive flag after receiving text
            r_flag = 0;

            // Reset flag variable
            f = 0;

            // Delay for processing received data
            delay_ms(20);

            // Clear previous scrolling text stored in EEPROM
            // Erase 30 bytes starting from address 0x0008
            ClrStr(0x0008,30);

            // Store blank spaces initially to avoid garbage data
            PageWrite_25LC512(0x0008,"   ");

            // Store new scrolling text into EEPROM
            // Address 0x000B is used for scrolling message storage
            PageWrite_25LC512(0x000B,rec_buff);

            // Reset buffer index
            index_val = 0;

            break;
    }
}
u8 menu_rtc[]="\r\n***RTC EDITING MODE***\r\n"
"D.Edit Date\r\n"
"T.Edit Time\r\n";
u8 str3[]="\r\nEnter The Date\r\nday date/month/year(Ex:5 15/05/2026) \r\n";
u8 str4[]="\r\nEnter The Time\r\nhour:min:sec(Ex:04:20:40)\r\n";
u8 format[]="\r\nInvalid Format\r\n";
u8 day_str[]="\r\nIncorrect Day\r\n";
u8 month_str[]="\r\nIncorrect Month\r\n";
u8 date_str[]="\r\nIncorrect Date\r\n";
u8 year_str[]="\r\nIncorrect Year\r\n";
u8 hour_str[]="\r\nIncorrect Hour\r\n";
u8 min_str[]="\r\nIncorrect Minute\r\n";
u8 sec_str[]="\r\nIncorrect second\r\n";
void edittime()
{
    int h, m, s;       // Variables to store hour, minute and second values

    while(1)
    {
INPUT:
        // Send time input format message through UART
        UART0_Str(str4);

        // Reset UART receive buffer index
        index_val = 0;

        // Wait until time data is received from UART
        while(r_flag != 1);

        // Clear receive flag after data reception
        r_flag = 0;

        // Reset flag variable
        f = 0;

        // Assign received buffer address to character pointer
        buffer = (char *)rec_buff;

        // Extract hour, minute and second values from received string
        // Expected format: HH:MM:SS
        if(sscanf(buffer,"%d:%d:%d",&h,&m,&s)!=3)
        {
            // Display incorrect format message
            UART0_Str(format);

            // Ask user to enter time again
            goto INPUT;
        }

        // Check hour range (0-23)
        if(!(h>=0 && h<=23))
        {
            // Display invalid hour message
            UART0_Str(hour_str);

            // Ask for time input again
            goto INPUT;
        }

        // Check minute range (0-59)
        if(!(m>=0 && m<=59))
        {
            // Display invalid minute message
            UART0_Str(min_str);

            // Ask for time input again
            goto INPUT;
        }

        // Check second range (0-59)
        if(!(s>=0 && s<=59))
        {
            // Display invalid second message
            UART0_Str(sec_str);

            // Ask for time input again
            goto INPUT;
        }

        // Update RTC time with valid hour, minute and second values
        SetRTCTimeInfo(h,m,s);

        // Exit loop after successfully setting time
        break;
    }
}


// Function to edit RTC date
void editdate()
{
    int d, dt, m, y, max_days;     // Variables for day, date, month, year and maximum days

    while(1)
    {
INPUT:
        // Send date input format message through UART
        UART0_Str(str3);

        // Store received UART buffer address
        buffer = (char *)rec_buff;

        // Reset UART receive buffer index
        index_val = 0;

        // Wait until date data is received
        while(r_flag != 1);

        // Clear receive flag
        r_flag = 0;

        // Reset flag variable
        f = 0;

        // Extract day, date, month and year from received string
        // Expected format: Day Date/Month/Year
        if(sscanf(buffer,"%d %d/%d/%d",&d,&dt,&m,&y)!=4)
        {
            // Display incorrect format message
            UART0_Str(format);

            // Ask user to enter date again
            goto INPUT;
        }

        // Validate day value (1-7)
        if(!(d>=1 && d<=7))
        {
            // Display invalid day message
            UART0_Str(day_str);

            // Ask for date input again
            goto INPUT;
        }

        // Validate month value (1-12)
        if(!(m>=1 && m<=12))
        {
            // Display invalid month message
            UART0_Str(month_str);

            // Ask for date input again
            goto INPUT;
        }


        // Calculate maximum number of days based on month
        if(m == 2)
        {
            // Check leap year condition for February
            if((y%4==0 && y%100!=0) || (y%400==0))
            {
                // Leap year February has 29 days
                max_days = 29;
            }
            else
            {
                // Normal February has 28 days
                max_days = 28;
            }
        }
        else if(m==4 || m==6 || m==9 || m==11)
        {
            // Months with 30 days
            max_days = 30;
        }
        else
        {
            // Remaining months have 31 days
            max_days = 31;
        }


        // Validate date range according to selected month
        if(!(dt>=1 && dt<=max_days))
        {
            // Display invalid date message
            UART0_Str(date_str);

            // Ask for date input again
            goto INPUT;
        }

        // Validate year range (0-2030)
        if(!(y>=0 && y<=2030))
        {
            // Display invalid year message
            UART0_Str(year_str);

            // Ask for date input again
            goto INPUT;
        }

        // Update RTC date with valid date, month and year
        SetRTCDateInfo(dt,m,y);

        // Update RTC day information
        SetRTCDay(d);

        // Exit loop after successfully setting date
        break;
    }
}
void time_edit_mode()
{
    // Clear dot matrix display before entering RTC edit mode
    display_str("    ",100);

    // Reset UART receive buffer index
    index_val = 0;

    // Display RTC edit menu through UART
    UART0_Str(menu_rtc);

    // Reset UART receive buffer index
    index_val = 0;

    // Wait until user selects an option from UART
    while(r_flag != 1);

    // Clear receive flag after receiving command
    r_flag = 0;

    // Check received command character
    switch(rec_buff[0])
    {
        // Case 'D' or 'd' for editing date
        case 'D':
        case 'd':

            // Call function to edit RTC date
            editdate();

            // Send confirmation message after date update
            UART0_Str("Date Updated successful\r\n");

            break;


        // Case 'T' or 't' for editing time
        case 'T':
        case 't':

            // Call function to edit RTC time
            edittime();

            // Send confirmation message after time update
            UART0_Str("Time Updated successful\r\n");

            break;
    }
}