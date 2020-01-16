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
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10); // Set compare mode for OCR1A
	TCCR1B = (1<<WGM13)|(0<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10); // Set Mode 1, PWM Phase correct 8-bit & 256 prescaler
	ICR1 = 125;
	TIMSK1 = 0b00000010;
	OCR1A = 0;
	DDRA = 0xFF; // Make pin A ports outputs, so we can trigger the H-Bridge.
}

void setSpeed(float speed) {
	
	//int dutyCycle = 0;
	//
	//if (speed > 254) {
		//dutyCycle = 254;
	//}
	//else if (speed <= 0) {
		//dutyCycle = 1;
	//}
	//else {
		//dutyCycle = speed;
	//}

	speed = speed / 100;
	OCR1A = (1-speed)*ICR1;
}