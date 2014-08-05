/************************

This is a module to initialize the PIC16LF1827 and to blink an LED

author: Osagie Igbeare

8/1/2014

*************************/

/**************** Header Files *********************/

#include "bitdefs.h"
#include <htc.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>

/***************** # Defines *****************/
#define LF1827_XT 0xFFF9;
#define LF1827_Hi_Volt_Prgm 0xDFFF;

/*************** module level variables ************/


/******* Function Prototypes ***************/

void ConfigSetUp(void);
void InitPorts(void);
void InitTimers(void);
void InitInterrupts(void);


/******* Acutal Functions ****************/

void ConfigSetUp(){

	CONFIG1 &= LF1827_XT;				// set Fosc to Medium Gain resonator/crystal (up to 4MHz)
	CONFIG2 &= LF1827_Hi_Volt_Prgm;		// MCLR pin must be raised to 8V to repgrom LF1827
}

void InitPorts(){

	ANSELA = 0x00;			// Port A pins are digital
	ANSELB = 0x00;			// Port B pins are digital

	TRISA = 0b11111011;		// 1 - input, 0 - output, RA2 is an output
	TRISB = 0b11011111;		// 1 - input, 0 - output, RB5 is an output

	PORTA = 0xFF;			// initialize LED to OFF
	PORTB = 0xFF;

}

void InitTimers(){

	T2CON = 0b01111110;		// Fosc / (4 instruct * 16 prescale * 16 postscale * 60 PR2) = 65 Hz
	PR2 = 60; 
}

void InitInterrupts(){

	INTCON = 0b11000000;	// Enable GIE, Enable PEIE
	PIE1 = 0b00000010; 		// Enable TMR2IE, interrupt when Timer 2 matches PR2
}

void interrupt ISR(){

	INTCON &= 0b00111111;   // Disable Interrupts

	if (TMR2IF){

		PORTA &= BIT2LO;	// turn LED on RA2 on by pulling pin low
		PORTB &= BIT5LO; 	// turn LED on RB6 on

		PIR1 &= BIT2LO;		// clears the TIMR2IF (timer 2 interrupt flag)

	}

	INTCON |= 0b11000000;	// ReEnable Interrupts
	return; 

}



/******** Main - which actually runs the code ***********/

void main (){

	// Initializing PIC16LF1827
	ConfigSetUp();
	InitPorts();
	InitTimers();
	InitInterrupts();

	while (true)
	{
		// some code will go here, I think...
	}


}


