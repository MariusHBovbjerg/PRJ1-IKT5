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

volatile unsigned char counter = 0;

volatile unsigned char MotorMode = 0;
ISR(INT2_vect){ //On rising edge, count + 1
	counter++;
}

ISR(INT3_vect){ //On rising edge, count + 1
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
	while(1){
	
	}
	
}