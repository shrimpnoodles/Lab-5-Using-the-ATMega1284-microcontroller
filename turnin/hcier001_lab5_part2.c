/*	Author: hcier001
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States {start, init, plus, minus, wait1, wait2, reset} state;
unsigned count;
unsigned button;
void Tick(){
	switch (state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if(button == 0x01){
				state = plus;
			}
			else if(button == 0x02){
				state = minus;
			}
			else if(button == 0x03){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		case plus:
			state = wait1;
			break;
		case minus:
			state = wait2;
			break;
		case wait1:
			if(button!=0x01){
				state = init;
			}
			else{
				state = wait1;
			}
			break;
		case wait2:
			if(button!=0x02){
				state = init;
			}
			else{
				state = wait2;
			}
			break;
		case reset:
			if(button !=0x03){
				state = init;
			}
			else{
				state = reset;
			}
			break;
		default:
			state = start;
			break;
	}
	switch (state) { //actions
		case init:
			break;
		case plus:
			if(count <9){
				count++;
			}
			break;
		case minus:
			if(count >0){
				count--;
			}
			break;
		case wait1:
			break;
		case wait2:
			break;
		case reset:
			count = 0;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00; PORTA = 0XFF;
	DDRB  =0Xff; PORTB = 0X00;
	DDRC = 0XFF; PORTC = 0X00;
	state = start;
    /* Insert your solution below */
    while (1) {
	button = ~PINA;
	button = (button & 0x07);
	count = 7;
	Tick();
	PORTC = count;
    }
    return 1;
}
