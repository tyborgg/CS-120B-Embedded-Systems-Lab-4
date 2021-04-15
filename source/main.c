/*	Author: tpast001
 *  Partner(s) Name: N/A
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*enum SM1_STATES {SM1_SMStart, SM1_B0, SM1_B1} SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_B0;
         		break;
      		case SM1_B0:
			if(A0 == 1)
				SM1_STATE = SM1_B1;
			else
				SM1_STATE = SM1_B0;
			break;
		case SM1_B1:
			if(A0 == 1)
				SM1_STATE = SM1_B0;
			else
				SM1_STATE = SM1_B1;
			break
      		default:
         		SM1_STATE = SM1_B0;
         		break;
   	}
   	switch(SM1_STATE) { 
      		case SM1_SMStart:
         		break;
      		case SM1_B0:
         		B0 = 1;
			B1 = 0;
         		break;
      		case SM1_B1:
         		B1 = 1;
			B0 = 0;
        		 break;
   	}
}*/

int main(void) {
	/*SM1_STATE = SM1_SMStart;

    	while(1){
		Tick_Toggle();
	}*/
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0xFF;

	unsigned char tempB0;
	unsigned char tempB1;
	unsigned char tempA1;

	while(1){
		tempB0 = PORTB & 0x01;
		tempB1 = PORTB & 0x02;
		tempA1 = PINA & 0x02;

		if(tempB0 == 1 && tempA1 == 1){
			B0 = 0;
			B1 = 1;
		}
		else if(tempB1 == 1 && tempA1 == 1){
			B0 = 1;
			B1 = 0;
		}
		else if(tempB0 == 1 && tempA1 == 0){
			B0 = 1;
			B1 = 0;
		}
		else if(tempB1 == 1 && tempA1 == 0){
			B0 = 0;
			B1 = 1;
		}
	}

	return 0;
}
