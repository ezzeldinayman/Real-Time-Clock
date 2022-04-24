/*
 * Real_Time_Clock.c
 *
 * Created: 20-Apr-22 2:48:21 PM
 *  Author: ezz_a
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "LCD.h"
#include "keypad.h"
#include "Seven_Segment.h"
#include <util/delay.h>
#include "Timers.h"
#include <avr/interrupt.h>
#include "std_macros.h"

void DisplayTime(char* time);
void CalculateTime(unsigned long totalSeconds, char* time);
void StopWatch(unsigned long seconds);
volatile unsigned char mux_flag = 0;
volatile unsigned long totalSeconds = 0;
volatile char* time = 0x300;


int main(void)
{
	LCD_vInit();
	LCD_vSend_string("Hello, World");
	keypad_vInit();
	seven_segment_vInit('B');
	DIO_vSETPORTDir('C',0x3F);
	
	sei();
	timer0_CTC_interrupt_Init();
	timer2_OV_interrupt_init();
	

	char* inputs = 0x320;
	char keypadInput = 0xFF;
	label:
	LCD_clearscreen();
	LCD_vSend_string("1 to set clock");
	LCD_movecursor(2,1);
	LCD_vSend_string("2 to start stopwatch");
	
    while(1)
    {
		do 
		{
			keypadInput = keypad_u8read();
		} while(keypadInput == 0xFF);
		
		if(keypadInput == '2')
		{
			LCD_clearscreen();
			LCD_vSend_string("0 to reset");
			LCD_movecursor(2,1);
			LCD_vSend_string("A to pause");
			unsigned long stopwatchTime = 0;
			totalSeconds=0;
			//stopwatch ON
			while(1)
			{
				if(keypad_u8read()=='A')
				{
					_delay_ms(180);
					stopwatchTime = totalSeconds;
					LCD_clearscreen();
					LCD_vSend_string("PAUSED");
					LCD_movecursor(2,1);
					LCD_vSend_string("Press A");
					do
					{
						CalculateTime(stopwatchTime,time);
						DisplayTime(time);
					}
					while (keypad_u8read() != 'A');
					_delay_ms(180);
					totalSeconds = stopwatchTime;
					LCD_clearscreen();
					LCD_vSend_string("BACK");	
				}
				
				if (keypad_u8read() == '0')
				{
					goto label;
				}
				
				StopWatch(totalSeconds);
			}				
				
			
		}
		
		
    }
}


void StopWatch(unsigned long seconds)
{
		CalculateTime(seconds, time);
		DisplayTime(time);
}


void DisplayTime(char* time)
{
	time = time+2;
	DIO_vWritePORT('C',0x1F);
	Seven_Segment_vWrite('B',(*time)%10);
	while(mux_flag==0);
	mux_flag = 0;
	
	
	DIO_vWritePORT('C',0x2F);
	Seven_Segment_vWrite('B',(*time)/10);
	while(mux_flag==0);
	mux_flag = 0;
	
	time--;
	
	DIO_vWritePORT('C',0x37);
	Seven_Segment_vWrite('B',(*time)%10);
	while(mux_flag==0);
	mux_flag = 0;
	
	DIO_vWritePORT('C',0x3B);
	Seven_Segment_vWrite('B',(*time)/10);
	while(mux_flag==0);
	mux_flag = 0;
	
	time--;
	
	DIO_vWritePORT('C',0x3D);
	Seven_Segment_vWrite('B',(*time)%10);
	while(mux_flag==0);
	mux_flag = 0;
	
	DIO_vWritePORT('C',0x3E);
	Seven_Segment_vWrite('B',(*time)/10);
	while(mux_flag==0);
	mux_flag = 0;
	
	time = time+2;
}

void CalculateTime(unsigned long totalSeconds, char* time)
{
	(*time) = totalSeconds/3600; //hours
	(*(time+1)) = (totalSeconds -(3600*(*time)))/60; //minutes
	(*(time+2)) = (totalSeconds -(3600 * (*time))-((*(time+1))*60)); //seconds
}
//void UpdateTime();

ISR(TIMER0_COMP_vect)
{
	mux_flag = 1; 
	
}

ISR(TIMER2_OVF_vect)
{
	totalSeconds++;
}
