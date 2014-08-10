#include <htc.h>
#include "bitdefs.h"

 __CONFIG(FCMEN_OFF & IESO_OFF & FOSC_XT & WDTE_OFF & MCLRE_OFF & PWRTE_OFF & BOREN_OFF 
		& LVP_ON & WRT_OFF & CPD_OFF & CP_OFF);

volatile char counter; 


void init (void)
{
	PIE1 = 0b00000001;
	INTCON = 0b11000000;
	// OPTION_REG = 0b10000000;
	TRISB = 0b00000000;
	TRISA = 0b00000000;
	T1CON = 0b00110101; 
}

void interrupt ISR(void)
{
	if ((TMR1IF))
	{
		counter++;
		PORTB = counter;
		PORTA ^= BIT2HI; 
		if ((counter % 2) != 0)
		{
			PORTA = BIT2HI;
			
		}
		else 
		{
			PORTA = BIT2LO;
		}
		TMR1IF = 0;
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
	