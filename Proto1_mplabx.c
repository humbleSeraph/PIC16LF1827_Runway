/************************

This is a module to initialize the PIC16LF1827 and to blink an LED

author: Osagie Igbeare

8/1/2014

*************************/

/**************** Header Files *********************/

#include <xc.h>
#include "pic.h"
#include <BitDefs.h>
#include "chip_select.h"


/*****************2Configuration Macros ***************/

//__CONFIG(FCMEN_OFF & IESO_OFF & FOSC_XT & WDTE_OFF & MCLRE_ON & PWRTE_OFF & BOREN_OFF
//		& LVP_ON & WRT_OFF & CPD_OFF & CP_OFF);

//CONFIG 1

#pragma config FOSC = XT
#pragma config WDTE = OFF       // Watchdog Timer Off
#pragma config PWRTE = OFF      // Power-up Timer Off
#pragma config MCLRE = ON       // MCLR Pin function is MCLR
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF

// CONFIG 2

#pragma config WRT = OFF
#pragma config LVP = ON


/***************** # Defines *****************/

/*************** module level variables ************/

static char counter; 


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
	PR2 = 250;
}

void InitInterrupts()
{

	PIE1 = 0b00000010; 		// Enable TMR2IE, interrupt when Timer 2 matches PR2	
	INTCON = 0b11000000;	// Enable GIE, Enable PEIE
	
}

void interrupt ISR()
{

	counter++; 
	if (TMR2IF)
	{
		if ((counter % 2) != 0)
		{
			PORTA |= BIT2HI;
			PORTB &= BIT5LO;
			
		}
		else 
		{
			PORTA &= BIT2LO;
			PORTB |= BIT5HI;
			counter = 0; 
		}

		TMR2IF = 0;		// clears the TIMR2IF (timer 2 interrupt flag)

	}
	return; 

}



/******** Main - which actually runs the code ***********/

void main ()
{

	// Initializing PIC16LF1827
	InitPorts();
	InitTimers();
	InitInterrupts();
	while(1)
	{

	}



}


