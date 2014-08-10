#include <htc.h>
_CONFIG(FOSC_XT & WDTE_OFF & PWRTE_OFF & BOREN_OFF 
		& LVP_ON & WRT_OFF & DEBUG_ON & CPD_OFF & CP_OFF);

void init (void)
{
	TRISB = 0b00000000;
}

char counter;

void main (void)
{
	counter = 0;
	init();
	while(1)
	{
		PORTB = counter;
		_delay(10000);
		counter++;

	}
	
}
	
	
	