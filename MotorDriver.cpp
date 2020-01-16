/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg & Kristian Gaardsted Bork
 */ 

#include "MotorDriver.h"
#include <stdio.h>
#include <avr/io.h>

void initMotor(){
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<WGM11)|(0<<WGM10); // Set compare mode 3 for OCR1A, clear on upcount, set on downcount.
	TCCR1B = (1<<WGM13)|(0<<WGM12)|(1<<CS12)|(0<<CS11)|(0<<CS10); // Set Mode 10, PWM Phase correct ICR1 TOP & 256 prescaler
	ICR1 = 125;
	TIMSK1 = 0b00000010;
	OCR1A = 0;
	DDRA = 0xFF; // Make pin A ports outputs, so we can trigger the H-Bridge.
}

void setSpeed(float speed) {
	
	if(speed > 100){
		speed = 100;
	}
	if(speed < 0){
		speed = 0;
	}
	speed = speed / 100;
	OCR1A = (1-speed)*ICR1;
}