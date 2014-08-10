#include <htc.h>
#include "bitdefs.h"
 //__CONFIG(FOSC_XT & WDTE_OFF & MCLRE_ON & PWRTE_OFF & BOREN_OFF 
//		& LVP_ON & WRT_OFF & CPD_OFF & CP_OFF);

volatile char counter; 


void init (void)
{
	PIE1 = 0b00000010;
	INTCON = 0b01000000;
	OPTION_REG = 0b10000000;
	TRISB = 0b00000000;
	T2CON = 0b01111110;
	PR2 = 200;
}

void interrupt ISR(void)
{
	if (TMR2IF)
	{
		counter++;
		TMR2IF = 0;
	}
}


void main (void) 
{
	counter = 0;
	init();
	ei(); 
	while(1)
	{
		PORTB = counter; 
	}
	
}
	