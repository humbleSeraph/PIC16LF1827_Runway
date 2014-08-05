/************************

This is a module to initialize the PIC16LF1827 and to blink an LED

author: Osagie Igbeare

8/1/2014

*************************/

/**************** Header Files *********************/

#include <bitdefs.h>
#include <htc.h>


/***************** Configuration Macros ***************/

__CONFIG(FOSC_XT & WDTE_OFF & MCLRE_ON & PWRTE_OFF & BOREN_OFF
		& LVP_ON & WRT_OFF & CPD_OFF & CP_OFF);


/***************** # Defines *****************/

/*************** module level variables ************/


/******* Function Prototypes ***************/

void InitPorts(void);
void InitTimers(void);
void InitInterrupts(void);


/******* Acutal Functions ****************/

void InitPorts()
{

	ANSELA = 0x00;			// Port A pins are digital
	ANSELB = 0x00;			// Port B pins are digital

	TRISA = 0b11111011;		// 1 - input, 0 - output, RA2 is an output
	TRISB = 0b11011111;		// 1 - input, 0 - output, RB5 is an output

	PORTA = 0xFF;			// initialize LED to OFF
	PORTB = 0xFF;

}

void InitTimers()
{

	T2CON = 0b01111110;		// Fosc / (4 instruct * 16 prescale * 16 postscale * 60 PR2) = 65 Hz
	PR2 = 60; 
}

void InitInterrupts()
{

	INTCON = 0b11000000;	// Enable GIE, Enable PEIE
	PIE1 = 0b00000010; 		// Enable TMR2IE, interrupt when Timer 2 matches PR2
}

void interrupt ISR()
{

	INTCON &= 0b00111111;   // Disable Interrupts

	if (TMR2IF)
	{

		PORTA &= BIT2LO;	// turn LED on RA2 on by pulling pin low
		PORTB &= BIT5LO; 	// turn LED on RB6 on

		TMR2IF = 0;		// clears the TIMR2IF (timer 2 interrupt flag)

	}

	INTCON |= 0b11000000;	// ReEnable Interrupts
	return; 

}



/******** Main - which actually runs the code ***********/

void main ()
{

	// Initializing PIC16LF1827
	InitPorts();
	InitTimers();
	InitInterrupts();



}


