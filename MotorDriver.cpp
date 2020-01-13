/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "MotorDriver.h"
#include <stdio.h>
#include <avr/io.h>

void initMotor(){
	TCCR1A = (1<<COM3A1)|(1<<COM3A0)|(0<<WGM31)|(1<<WGM30); // Set compare mode for OCR1A
	TCCR1B = (0<<WGM33)|(0<<WGM32)|(1<<CS32)|(0<<CS31)|(0<<CS30); // Set Mode 1, PWM Phase correct 8-bit & 256 prescaler
	TIMSK1 = 0b00000010;
	OCR1A = 0;
	DDRA = 0xFF; // Make pin a ports outputs, so we can trigger the H-Bridge.
}

void forwardMotor(int setting){
	 setting = 1;
}

void reverseMotor(int setting){
	setting = 2;
}

void stopMotor(int setting){
	setting = 0;
}

void setSpeed(int speed) {
	
	int dutyCycle = 0;
	
	if (speed > 254) {
		dutyCycle = 254;
	}
	else if (speed <= 0) {
		dutyCycle = 1;
	}
	else {
		dutyCycle = speed;
	}

	OCR1A = dutyCycle;
}