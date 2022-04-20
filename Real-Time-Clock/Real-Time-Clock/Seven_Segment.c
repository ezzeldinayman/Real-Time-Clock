/*
 * Seven_Segment.c
 *
 * Created: 20-Apr-22 2:51:00 PM
 *  Author: ezz_a
 */ 
#include "DIO.h"
#include <avr/io.h>


void seven_segment_vInit(unsigned char portname)
{
	switch(portname)
	{
		case 'A':
		case 'a':
		{
			DIO_vSETPORTDir('A',0xFF);
		}
		break;
		
		case 'B':
		case 'b':
		{
			DIO_vSETPORTDir('B',0xFF);
		}
		break;
		
		case 'C':
		case 'c':
		{
			DIO_vSETPORTDir('C',0xFF);
		}
		break;
		
		case 'D':
		case 'd':
		{
			DIO_vSETPORTDir('D',0xFF);
		}
		break;						
	}
}

void Seven_Segment_vWrite(unsigned char portname, unsigned char number)
{
	unsigned char arr[10] = {0x3F, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
	DIO_vWritePORT(portname, arr[number]);
}