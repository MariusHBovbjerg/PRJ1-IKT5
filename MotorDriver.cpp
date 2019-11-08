/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "includes.h"

void initMotor(){
	TCCR1A = 0b00100010; // Set compare mode for OC1A
	TCCR1B = 0b00011101; // Set Mode 14, FAST PWM TOP = ICR1 & 1024 prescaler
	ICR1 = 156; // TOP value
	OCR1A = 0; // Compare value, 0 = 0% duty cycle, 156 = 100% duty cycle
}

void forward(){
	
}

void reverse(){
	
}

void setSpeed(char speed) {
	
	char dutyCycle;
	
	if (speed > 100) {
		char dutyCycle = 100;
	}
	else {
		char dutyCycle = speed;
	}

	OCR1A = (float)(dutyCycle * 1.56);
}