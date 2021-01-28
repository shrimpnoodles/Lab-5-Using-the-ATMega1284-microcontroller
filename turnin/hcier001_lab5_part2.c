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
unsigned char count;
//unsigned char button=~PINA;
void Tick(){
	switch (state) { //transitions
		case start:
			state = init;
			break;
		case init:
			if((~PINA&0x03) == 0x01){
				state = plus;
			}
			else if((~PINA&0x03) == 0x02){
				state = minus;
			}
			else if((~PINA&0x03) == 0x03){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		case plus:
			//state = wait1;
			if((~PINA&0x03)==0x02){
				state = minus;
			}
			else if((~PINA&0x03)== 0x03){
				state = reset;
			}
			else if((~PINA&0x03)==0x00){
				state = init;
			}
			else{
				state = plus;
			}
			break;
		case minus:
			//state = wait2;
			if((~PINA&0x03) == 0x03){
				state = reset;
			}
			else if((~PINA&0x03) == 0X00){
				state = init;
			}
			else if((~PINA&0x03) == 0X01){
				state = plus;
			}
			else {
				state = minus;
			}
			break;
		/*case wait1:
			if(~PINA!=0x01){
				state = init;
			}
			else{
				state = wait1;
			}
			break;
		case wait2:
			if(~PINA!=0x02){
				state = init;
			}
			else{
				state = wait2;
			}
			break;*/
		case reset:
			if((~PINA&0x03) ==0x03){
				state = reset;
			}
			else{
				state = init;
			}
			break;
		default:
			state = start;
			break;
	}
	switch (state) { //actions
		case init:
			if((~PINA&0x03)==0x01){
				if(count <9){
				count++;
				}
			}
			else if((~PINA&0x03) ==0x02){
				if(count >0){
				count --;
				}
			}
			else if((~PINA&0x03)==0x03){
				count = 0;
			}
			break;
		case plus:
			//if(count <9){
			//	count = count +1;
			//}
			if((~PINA&0x03)== 0x02){
				if(count >0){
					count--;
				}
			}
			else if((~PINA&0x03) ==0x03){
				count =0;
			}
			break;
		case minus:
			//if(count >0){
			//	count= count -1;
			//}
			if((~PINA&0x03) ==0x01){
				if(count <9){
				count++;
				}
			}
			else if((~PINA&0x03) ==0x03){
				count =0;
			}
			break;
		/*case wait1:
			break;
		case wait2:
			break;*/
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
//	button =~PINA;
//	button = (button&0x07);
	count =7;
    /* Insert your solution below */
    while (1) {
	Tick();
	PORTC = count;
    }
    return 1;
}
