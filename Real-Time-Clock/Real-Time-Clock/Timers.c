/*
 * Timers.c
 *
 * Created: 20-Apr-22 3:58:20 PM
 *  Author: ezz_a
 */ 
#include "std_macros.h"
#include <avr/io.h>


void timer0_CTC_interrupt_Init()
{
	SET_BIT(TCCR0,WGM01);
	OCR0 = 40;
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);
	SET_BIT(TIMSK,OCIE0);
}

void timer2_OV_interrupt_init()
{
	//overflow mode
	
	SET_BIT(ASSR,AS2);
	
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	//external clock enable and prescaler is 128, now we need to connect 32768Hz Crystal
	SET_BIT(TIMSK,TOIE2);
}