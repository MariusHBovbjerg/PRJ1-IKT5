/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 
#define F_CPU 16000000
#define MAX_LED_NR 7
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "MotorDriver.h"
#include "FLightDriver.h"
#include "Counter.h"
#include "SoundDriver.h"
#include "BLightDriver.h"

unsigned char counter = 0;

bool newCount = true;

volatile unsigned char MotorMode = 0;

ISR(INT4_vect){ //On rising edge, count + 1
	newCount = true;
	counter++;
}


ISR(TIMER1_COMPA_vect){
	                                                                                                                                                                        
	switch(MotorMode){
		case 0:
			PORTA = 0b00000000;
		break;
		case 1:
			PORTA = 0b00000001;
		break;
		case 2:
			PORTA = 0b00000010;
		break;
		default:
			PORTA = 0b00000000;
		break;
			
	}
}

int main(void)
{
	sei();
	initCounter();
	initMotor();
	InitUART(9600,8,false);
	counter = 0;
	while(1){
		
		if(newCount){
			switch(counter){
				case 1:
					newCount = false;
					SendInteger(1);
					SendChar('\n');
					break;
				case 2:
					newCount = false;
					SendInteger(2);
					SendChar('\n');
					break;
					
				case 3:
					newCount = false;
					SendInteger(3);
					SendChar('\n');
					break;
				case 4:
					newCount = false;
					SendInteger(4);
					SendChar('\n');
					break;
				case 5:
					newCount = false;
					SendInteger(5);
					SendChar('\n');
					break;
				case 6:
					newCount = false;
					SendInteger(6);
					SendChar('\n');
					break;
				case 7:
					newCount = false;
					SendInteger(7);
					SendChar('\n');
					break;
				case 8:
					newCount = false;
					SendInteger(8);
					SendChar('\n');
					break;
				case 9:
					newCount = false;
					SendInteger(9);
					SendChar('\n');
					break;
				case 10:
					newCount = false;
					SendInteger(10);
					SendChar('\n');
					break;
				default:
				
					newCount = false;
					SendString("Out of bounds\n");
					break;
				
			}
		}
		_delay_ms(100);
	}
	
}