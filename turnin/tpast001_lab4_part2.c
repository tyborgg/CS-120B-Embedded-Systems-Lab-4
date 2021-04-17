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

enum SM1_STATES {SM1_SMStart, SM1_up, SM1_down, SM1_Wait, SM1_reset, SM1_Waitup, SM1_Waitdown} SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_Wait;
         		break;

		case SM1_Wait:
			if(PINA == 0x01 && PORTC != 9){
				SM1_STATE = SM1_up;
			}
			else if(PINA == 0x02 && PORTC != 0){
				SM1_STATE = SM1_down;
			}
			else if(PINA == 0x03){
				SM1_STATE = SM1_reset;
			}
			else{
				SM1_STATE = SM1_Wait;
			}      		
			break;

		case SM1_up:
			SM1_STATE = SM1_Wait;
			break;

		case SM1_down:
			SM1_STATE = SM1_Wait;
			break;

		case SM1_reset:
			SM1_STATE = SM1_Wait;
			break;

		case SM1_Waitdown:
			if(PINA == 0x01){
				SM1_STATE = SM1_Waitdown;
			}
			else if(PINA == 0x00){		
				SM1_STATE = SM1_Wait;
			}
			break;
		
		case SM1_Waitup:
			if(PINA == 0x02){
				SM1_STATE = SM1_Waitup;
			}
			else if(PINA == 0x00){		
				SM1_STATE = SM1_Wait;
			}			
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
      		
		case SM1_up:
         		PORTC++;
         		break;

      		case SM1_down:
         		PORTC--;
        		break;

		case SM1_reset:
         		PORTC = 0x00;
        		break; 

		case SM1_Waitdown:
        		break;

		case SM1_Waitup:
        		break;	
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTB = 0x00;

	PORTC = 0x07;

	SM1_STATE = SM1_SMStart;

	while(1){
		Tick_Toggle();
	}

	return 0;
}
