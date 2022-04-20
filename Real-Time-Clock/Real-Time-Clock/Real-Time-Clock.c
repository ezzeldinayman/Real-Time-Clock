/*
 * Real_Time_Clock.c
 *
 * Created: 20-Apr-22 2:48:21 PM
 *  Author: ezz_a
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Seven_Segment.h"
#include <util/delay.h>
#include "Timers.h"
#include <avr/interrupt.h>
#include "std_macros.h"

void DisplayTime(char* time);
void updateTime(unsigned long totalSeconds, char* time);
volatile unsigned char mux_flag = 0;
volatile unsigned long totalSeconds = 0;



int main(void)
{
	seven_segment_vInit('D');
	sei();
	timer0_CTC_interrupt_Init();
	timer2_OV_interrupt_init();
	DIO_vSETPORTDir('C',0x3F);
	DIO_vSETPORTDir('B',0xFF);
	//unsigned long totalSeconds = 0;
	char* time = 0x300;
    while(1)
    {

		updateTime(totalSeconds, time);
		DisplayTime(time);
    }
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

void updateTime(unsigned long totalSeconds, char* time)
{
	(*time) = totalSeconds/3600; //hours
	(*(time+1)) = (totalSeconds -(3600*(*time)))/60; //minutes
	(*(time+2)) = (totalSeconds -(3600 * (*time))-((*(time+1))*60)); //seconds
}

ISR(TIMER0_COMP_vect)
{
	mux_flag = 1; 
	
}

ISR(TIMER2_OVF_vect)
{
	totalSeconds++;
}
