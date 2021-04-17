/*	Author: tpast001
 *  Partner(s) Name: N/A
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM1_STATES {SM1_SMStart, SM1_pound, SM1_lock, SM1_unlocked, SM1_Waitpound, SM1_Y} SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_lock;
         		break;

		case SM1_lock:
			if(PINA == 0x03){
				SM1_STATE = SM1_pound;
			}
			else if(PINA == 0x02 || PINA == 0x01){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_lock;
			}      		
			break;

		case SM1_pound:
			if(PINA == 0x03){
				SM1_STATE = SM1_pound;	
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_Waitpound;
			}
			else{
				SM1_STATE = SM1_lock;
			}
			break;

		case SM1_Y:
			if(PINA == 0x02){
				SM1_STATE = SM1_Y;
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_unlocked;
			}
			else{
				SM1_STATE = SM1_lock;
			}
			break;
/*
		case SM1_X:
			SM1_STATE = SM1_lock;
			break;*/
		
		case SM1_Waitpound:
			if(PINA == 0x02){
				SM1_STATE = SM1_Y;
			}
			else if(PINA == 0x80){
				SM1_STATE = SM1_lock;
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_Waitpound;
			}
			else{
				SM1_STATE = SM1_lock;	
			}
			break;

		case SM1_unlocked:
			if(PINA == 0x80){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}
			break;

      		default:
         		SM1_STATE = SM1_lock;
         		break;
   	}

   	switch(SM1_STATE) { 
      		case SM1_SMStart:
         		break;

		case SM1_lock:
			PORTB = 0x00;
         		break;
      		
		case SM1_pound:
         		break;

      		case SM1_Waitpound:
        		break;
			
		case SM1_Y:
        		break;

		case SM1_unlocked:
         		PORTB = 0x01;
        		break; 	
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	PORTB = 0x00;

	SM1_STATE = SM1_SMStart;

	while(1){
		Tick_Toggle();
	}

	return 0;
}
