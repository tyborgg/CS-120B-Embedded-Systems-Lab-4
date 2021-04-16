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

enum SM1_STATES {SM1_SMStart, SM1_B0, SM1_B1, SM1_Wait} SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_B0;
         		break;

		case SM1_Wait:
			if(PORTB == 0x01 && PINA == 0x01){
				SM1_STATE = SM1_B1;
			}
			else if(PORTB == 0x02 && PINA == 0x01){
				SM1_STATE = SM1_B0;
			}
			else{
				SM1_STATE = SM1_Wait;
			}      		
			break;

		case SM1_B0:
			SM1_STATE = SM1_Wait;
			break;

		case SM1_B1:
			SM1_STATE = SM1_Wait;
			break;

      		default:
         		SM1_STATE = SM1_Wait;
         		break;
   	}

   	switch(SM1_STATE) { 
      		case SM1_SMStart:
         		break;

		case SM1_Wait:
         		break;
      		
		case SM1_B0:
         		PORTB = 0x01;
         		break;

      		case SM1_B1:
         		PORTB = 0x02;
        		 break;
   	}
}

int main(void) {/
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	PORTB = 0x01;

	SM1_STATE = SM1_SMStart;

	while(1){
		TickToggle();
	}

	return 0;
}
