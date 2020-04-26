/*	Author: Garrett Yamano
 *  Partner(s) Name: 
 *	Lab Section: 022
 *	Assignment: Lab #5 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://youtu.be/mymmkFd2gF4

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	unsigned char temp = 0x00; // Temporary variable to hold PINA
	unsigned char hold = 0x00; // Temporary variable to hold temp
	while (1) {
		temp = ~PINA;
		hold = ((temp >= 1) << 5) + ((temp >= 3) << 4) + ((temp >= 5) << 3) + ((temp >= 7) << 2) + ((temp >= 10) << 1) + ((temp >= 13) << 0) + ((temp <= 4) << 6);
		if(temp == 0x83){
			hold = 0x70;
		}
		PORTC = hold;
	}
	return 0;
}
