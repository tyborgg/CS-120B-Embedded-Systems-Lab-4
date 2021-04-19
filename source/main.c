/*	Author: tpast001
 *  Partner(s) Name: N/A
 *	Lab Section: 023
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int code[] = {0x04, 0x01, 0x02, 0x01};
int temp[4];
int count = 0;

enum SM1_STATES {SM1_SMStart, SM1_lock, SM1_unlocked, SM1_reset1, SM1_reset2} SM1_STATE; //SM1_Wait1, SM1_Wait2 } SM1_STATE;
void Tick_Toggle() { 
	switch(SM1_STATE) { 
     		case SM1_SMStart:
      			SM1_STATE = SM1_lock;
         		break;

		case SM1_lock:
			if(PINA == code[count]){
				if(count == 3){
					SM1_STATE = SM1_reset1;
				}
				else{
					temp[count] = PINA;
					count += 1;	
					SM1_STATE = SM1_lock;
				}
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_lock;		
			}
			else if(count == 3 && (temp[0] != code[0] || temp[1] != code[1] || temp[2] != code[2] || PINA != code[3])){
				SM1_STATE = SM1_reset1;
			} 		
			else {
				SM1_STATE = SM1_lock;
			}
			break;

		case SM1_unlocked:
			if(PINA == code[count]){
				if(count == 3){
					SM1_STATE = SM1_lock;
				}
				else{
					temp[count] = PINA;
					count += 1;
					SM1_STATE = SM1_unlocked;
				}
			}
			else if(PINA == 0x00){
				SM1_STATE = SM1_unlocked;		
			}		
			else if(PINA == 0x80){
				SM1_STATE = SM1_lock;
			}
			else if(count == 3 && (temp[0] != code[0] || temp[1] != code[1] || temp[2] != code[2] || PINA != code[3])){
				SM1_STATE = SM1_reset2;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}		
			break;
		
		case SM1_reset1:
			if(count == 3){
				SM1_STATE = SM1_unlocked;
			}
			else{
				SM1_STATE = SM1_lock;
			}						
			break;

		case SM1_reset2:
			if(count == 3){
				SM1_STATE = SM1_lock;
			}
			else{
				SM1_STATE = SM1_unlocked;
			}		
			break;			
		
	/*	case SM1_Wait1:
			if(PINA == code[count]){
				if(count == 3){
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
				if(count == 3){
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
			break; */

      		default:
         		SM1_STATE = SM1_lock;
         		break;
   	}

   	switch(SM1_STATE) { 
      		case SM1_SMStart:
         		break;

		case SM1_lock:
			PORTB = 0x00;
			//count = 0;
         		break;

		case SM1_reset1:
			count = 0;
			break;

		case SM1_reset2:
			count = 0;
			break;

		/*case SM1_Wait1:
        		break;

		case SM1_Wait2:
        		break;*/

		case SM1_unlocked:
         		PORTB = 0x01;
			//count = 0;
        		break; 	
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	//PORTB = 0x00;
	count = 0;
	SM1_STATE = SM1_SMStart;

	while(1){
		Tick_Toggle();
	}

	return 0;
}
