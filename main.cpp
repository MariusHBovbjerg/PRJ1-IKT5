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
#include "led.h"

volatile unsigned char counter = 0;

ISR(INT2_vect){ //On rising edge, count + 1
	counter++;
}

ISR(INT3_vect){ //On rising edge, count + 1
	counter++;
}

ISR(USART0_RX_vect){
	char character = UDR0;
	switch(character){
		case '0':
			turnOnLED(0);
			SendString("Led 0 is turned on\n");
		break;
		case '1':
			turnOnLED(1);
			SendString("Led 1 is turned on\n");
		break;
		case '2':
			turnOnLED(2);
			SendString("Led 2 is turned on\n");
		break;
		case '3':
			turnOnLED(3);
			SendString("Led 3 is turned on\n");
		break;
		case '4':
			turnOnLED(4);
			SendString("Led 4 is turned on\n");
		break;
		case '5':
			turnOnLED(5);
			SendString("Led 5 is turned on\n");
		break;
		case '6':
			turnOnLED(6);
			SendString("Led 6 is turned on\n");
		break;
		case '7':
			turnOnLED(7);
			SendString("Led 7 is turned on\n");
		break;
		default:
			writeAllLEDs(0);
			SendString("Invalid input, all LEDs off\n");
		break;
		
	}
}

void adcInit(){
	 // PF pins are inputs (ADC)
	 DDRF = 0;
	 // Internal 5 volt reference, ADLAR = 0, Input = ADC0 single ended
	 ADMUX = 0b01000000;
	 // ADC enable
	 // ADC interrupt disabled
	 // ADC prescaler = 128 (=> ADC clock = 16 MHz / 128 = 125 kHZ)
	 ADCSRA = 0b10000111;
	
}
void Init_Timer3()
{
	// OC3A = PE, pin 3 : Set as output pin
	DDRE |= (1<<3);
	// Mode = 3 (PWM, Phase Correct, 10 bit)
	// Set OC3A on match down counting / Clear OC3A on match up counting
	// Clock prescaler = 1
	TCCR3A = 0b10000011;
	TCCR3B = 0b00000001;
	// Duty cycle = 50%
	OCR3A = 1024/2;
}


int main(void)
{
    //initCounter();
    //while (1) 
    //{
		//
		//
    //}
	// Initialize LED port
	initLEDport();
	// Initialize UART: Baud = 9600, 8 data bits, No Parity
	InitUART(9600, 8, 0);
	Init_Timer3();
	adcInit();
	unsigned int ADC_Potentiometer, ADC_PWM;


	while(1){
	ADMUX = 0b01000000;
	ADCSRA |= 0b01000000;
	while(ADCSRA & 0b01000000){
		
	}
	ADC_Potentiometer = ADCW;
	SendString ("ADC0 = ");
	SendInteger(ADC_Potentiometer);
	SendChar('\n');
	ADMUX = 0b01000001;
	ADCSRA |= 0b01000000;
	while(ADCSRA & 0b01000000){
		
	}
	ADC_PWM = ADCW;
	SendString ("ADC1 = ");
	SendInteger(ADC_PWM);
	SendChar('\n');
	}
	
}