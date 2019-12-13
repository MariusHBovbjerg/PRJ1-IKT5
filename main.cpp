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

ISR(INT4_vect){ //On rising edge, count + 1
	counter++;
	SendInteger(counter);
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
	//while(1){
		
		setSpeed(50);
		
		_delay_ms(10);
		
		forwardMotor(MotorMode);
		
		_delay_ms(250);
		
		setSpeed(70);
		
		_delay_ms(250);
		
		setSpeed(80);
		
		_delay_ms(250);
		
		setSpeed(90);
		
		_delay_ms(250);
		
		setSpeed(100);
		
		_delay_ms(250);
		
		reverseMotor(MotorMode);
		
		_delay_ms(250);
		
		stopMotor(MotorMode);
		
		_delay_ms(250);
		
		reverseMotor(MotorMode);
		
		_delay_ms(250);
		
		setSpeed(100);
		
		_delay_ms(250);
		
		setSpeed(90);
		
		_delay_ms(250);
		
		setSpeed(80);
		
		_delay_ms(250);
		
		setSpeed(70);
		
		_delay_ms(250);
		
		stopMotor(MotorMode);
	//}
	
}