/*	Author: Garrett Yamano
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #5 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: link_to_video.com

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Init, Pattern, Reset} state;

unsigned char cnt;
unsigned char hold;

void Tick(){
	switch(state){
		case Start: // Initial transition
			cnt = 0x00;
			hold = 0x00;
			state = Init;
			break;
		case Init:
			hold = 0x00;
			if((~PINA & 0xFF) == 0x01){
				cnt += 1;
				state = Pattern;
			}
			else{
				state = Init;
			}
			break;
		case Pattern:
			if((~PINA & 0xFF) == 0x01){
				state = Pattern;
			}
			else if(((~PINA & 0xFF) == 0x00) && (cnt >= 0x07)){
				state = Reset;
			}
			else{
				state = Init;
			}
			break;
		case Reset:
			state = Init;
			hold = 0x00;
			cnt = 0x00;
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Init:
			break;
		case Pattern:
			if(cnt == 0x01){
				hold = 0x01;
			}
			else if(cnt == 0x02){
				hold = 0x21;
			}
			else if(cnt == 0x03){
				hold = 0x23;
			}
			else if(cnt == 0x04){
				hold = 0x33;
			}
			else if(cnt == 0x05){
				hold = 0x37;
			}
			else if(cnt == 0x06){
				hold = 0x3F;
			}
			else{
				hold = 0x3F;
			}
			PORTB = hold;
			break;
		case Reset:
			PORTB = 0x00;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	state = Start;
	while (1) {
		Tick();	
	}
	return 0;
}

