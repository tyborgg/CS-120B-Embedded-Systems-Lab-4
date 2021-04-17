/*	Author: tpast001
 *  Partner(s) Name: N/A
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int code[] = {0x01, 0x02, 0x01};
int count = 0;

enum SM1_STATES {SM1_SMStart, SM1_pound, SM1_lock, SM1_unlocked,SM1_Wait1, SM1_Wait2 }SM1_STATE;//SM1_Waitpound, SM1_Y, SM1_Lockpound, SM1_WaitLockpound, SM1_LockY} SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_lock;
         		break;

		case SM1_lock:
			if(PINA == 0x04){
				SM1_STATE = SM1_Wait1;
			}
			else if(PINA == 0x02 || PINA == 0x01){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_lock;
			}      		
			break;
/*
		case SM1_pound:
			if(PINA == 0x04){
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

		case SM1_X:
			SM1_STATE = SM1_lock;
			break;
		
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
*/
		case SM1_unlocked:
			if(PINA == 0x80){
				SM1_STATE = SM1_lock;
			}
			else if(PINA == 0x04){
				SM1_STATE = SM1_Wait2;
			}		
			else{
				SM1_STATE = SM1_unlocked;
			}
			break;
		
		case SM1_Wait1:
			if(PINA == code[count]){
				if(count == 2){
					SM1_STATE = SM1_unlocked;
				}
				else{
					count++;
					SM1_STATE = SM1_Wait1;
				}
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_Wait1;		
			}
			else{
				SM1_STATE = SM1_lock;
			}
			break;

		
		case SM1_Wait2:
			if(PINA == code[count]){
				if(count == 2){
					SM1_STATE = SM1_lock;
				}
				else{
					count++;
					SM1_STATE = SM1_Wait2;
				}
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_Wait2;		
			}
			else if(PINA == 0x80){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}
			break;
/*
		case SM1_Lockpound:
			if(PINA == 0x04){
				SM1_STATE = SM1_Lockpound;	
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_WaitLockpound;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}
			break;

		case SM1_LockY:
			if(PINA == 0x02){
				SM1_STATE = SM1_LockY;
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}
			break;
		
		case SM1_WaitLockpound:
			if(PINA == 0x02){
				SM1_STATE = SM1_LockY;
			}
			else if(PINA == 0x80){
				SM1_STATE = SM1_unlocked;
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_WaitLockpound;
			}
			else{
				SM1_STATE = SM1_unlocked;	
			}
			break;*/

		

      		default:
         		SM1_STATE = SM1_lock;
         		break;
   	}

   	switch(SM1_STATE) { 
      		case SM1_SMStart:
         		break;

		case SM1_lock:
			PORTB = 0x00;
			count = 0;
         		break;
      /*		
		case SM1_pound:
         		break;

      		case SM1_Waitpound:
        		break;
			
		case SM1_Y:
        		break;

		case SM1_Lockpound:
         		break;

      		case SM1_WaitLockpound:
        		break;
			
		case SM1_LockY:
        		break;	*/

		case SM1_Wait1:
        		break;

		case SM1_Wait2:
        		break;

		case SM1_unlocked:
         		PORTB = 0x01;
			count = 0;
        		break; 	
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	//PORTB = 0x00;

	SM1_STATE = SM1_SMStart;

	while(1){
		Tick_Toggle();
	}

	return 0;
}
