#include <htc.h>
#include "bitdefs.h"
#include "pic.h"
#include "chip_select.h"

 __CONFIG(FCMEN_OFF & IESO_OFF & FOSC_XT & WDTE_OFF & MCLRE_OFF & PWRTE_OFF & BOREN_OFF 
		& LVP_ON & WRT_OFF & CPD_OFF & CP_OFF);

volatile char counter; 


void init (void)
{
	PIE1 = 0b00000010;
	INTCON = 0b11000000;
	// OPTION_REG = 0b10000000;
	TRISB = 0b00000000;
	TRISA = 0b00000000;
	T2CON = 0b01111110; 
	PR2 = 60; 
}

void interrupt ISR(void)
{
	if ((TMR2IF))
	{
		counter++;
		PORTB = counter;

		if ((counter % 2) != 0)
		{
			PORTA |= BIT2HI;
			
		}
		else 
		{
			PORTA &= BIT2LO;
			counter = 0; 
		}

		TMR2IF = 0;
	}
}


void main (void) 
{
	counter = 0;
	init();
	//ei(); 
	PORTA = 0b00000000;	
	while(1)
	{

	}
	
}
	