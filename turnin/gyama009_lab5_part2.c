/*	Author: Garrett Yamano
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #5 Exercise #2
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

enum States{Start, Init, Increment, Decrement, Reset} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			PORTC = 0x00;
			state = Init;
			break;
		case Init:
			if((~PINA & 0xFF) == 0x01){
				state = Increment;
				if(PORTC <= 0x08){
					PORTC += 0x01;
				}
			}
			else if(((~PINA & 0xFF) == 0x02)){
				state = Decrement;
				if(PORTC >= 0x01){
					PORTC -= 0x01;
				}
			}
			else if(((~PINA & 0xFF) == 0x03)){
				state = Reset;
			}
			else{
				state = Init;
			}
			break;
		case Increment:
			if((~PINA & 0xFF) == 0x00){
				state = Init;
			}
			else if((~PINA & 0xFF) == 0x03){
				state = Reset;
			}
			else{
				state = Increment;
			}
			break;
		case Decrement:
			if((~PINA & 0xFF) == 0x00){
				state = Init;
			}
			else if((~PINA & 0xFF) == 0x03){
				state = Reset;
			}
			else{
				state = Decrement;
			}
			break;
		case Reset:
			if(((~PINA & 0xFF) == 0x03) || ((~PINA & 0xFF) == 0x02) ||((~PINA & 0xFF) == 0x01)){
				state = Reset;
			}
			else{
				state = Init;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Init:
			break;
		case Increment:
			break;
		case Decrement:
			break;
		case Reset:
			PORTC = 0x00;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	state = Start;
	while (1) {
		Tick();	
	}
	return 0;
}

