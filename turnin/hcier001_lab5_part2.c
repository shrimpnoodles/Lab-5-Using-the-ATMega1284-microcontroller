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
enum States {start, init, p0push, p1push, wait1, wait2, reset} state;
unsigned portcCount;
void Tick(){
	switch(state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if((~PINA&0x03) == 0x01 && portcCount < 9){
				state = p0push;
			}
			else if((~PINA&0x03)== 0x02){
				state = p1push;
			}
			else if((~PINA&0x03)== 0x03){
				state = reset;
			}
			break;
		case p0push:
			state = wait1;
			break;
		case wait1:
			if((~PINA&0x03) == 0x02){
				state = p1push;
			}
			else if((~PINA&0x03) == 0x03){
				state = reset;
			}
			else{
				state = wait1;
			}
			break;
		case p1push:
			state = wait2;
			break;
		case wait2:
			if((~PINA&0x03)==0x03){
				state = reset;
			}
			else if((~PINA&0x03)==0x01){
				state = p0push;
			}
			else{
				state = wait2;
			}
			break;
		case reset:
			if((~PINA&0x03) == 0x03){
				state = reset;
			}
			else if((~PINA&0x03)==0x01){
				state = p0push;
			}
			else if((~PINA&0x03)==0x02){
				state = p1push;
			}
			break;
		default:
			state = start;
			break;
		}
	switch(state){ //actions
		case init:
			portcCount = 7;
			break;
		case p0push:
			if(portcCount < 9){
				portcCount = portcCount +1;
			}
			break;
		case p1push: 
			if(portcCount > 0){
				portcCount = portcCount -1;
			}
			break;
		case wait1:
			break;
		case wait2:
			break;
		case reset:
			portcCount =0;
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0X00; PORTA = 0XFF;
	DDRB = 0XFF; PORTB = 0X00;
	DDRC = 0xFF; PORTC = 0X00;
	state = start;
	portcCount = 7;
    /* Insert your solution below */
    while (1) {
	Tick();
	PORTC = portcCount;
    }

    return 1;
}
