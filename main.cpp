/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg & Magnus Gjøttrup & Emil Engstrøm & Anders Schou Pedersen
 */ 
#define F_CPU 16000000
#define MAX_LED_NR 7
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MotorDriver.h"
#include "FLightDriver.h"
#include "Sensor.h"
#include "SoundDriver.h"
#include "BLightDriver.h"

volatile int counter = 0;
volatile bool newCount = true;

volatile unsigned int MotorMode = 0;

void InitUARTnul(unsigned long BAUD)
{
	
	UCSR0B = 0b00011000;
	
	UCSR0C = 0b00000110;
	
	UBRR0L = ((F_CPU/(16*BAUD))-1);
}

void SendCharnul(char Tegn)
{
	while(!(UCSR0A & (1<<UDRE0))){
		
	}
	UDR0 = Tegn;
}

void SendString(char* Streng)
{
	while(*Streng != '\0'){
		SendCharnul(*Streng);
		Streng++;
	}
}

void SendInteger(int Tal)
{
	char intStr[30];
	itoa(Tal, intStr, 10);
	SendString(intStr);
}


ISR(INT4_vect){ //On rising edge, count + 1
	if(counter == 3){
		
		newCount = true;
		counter++;
		EIMSK = 0b00000000;
		_delay_ms(500);
		EIFR = 0b00110000;
		EIMSK = 0b00110000;
	}
	else {
		newCount = true;
		counter++;
		EIMSK = 0b00000000;
		_delay_ms(300);
		EIFR = 0b00110000;
		EIMSK = 0b00110000;
	}
}
ISR(INT5_vect){
	if(counter == 3){
		
		newCount = true;
		counter++;
		EIMSK = 0b00000000;
		_delay_ms(500);
		EIFR = 0b00110000;
		EIMSK = 0b00110000;
	}
	else {
		newCount = true;
		counter++;
		EIMSK = 0b00000000;
		_delay_ms(300);
		EIFR = 0b00110000;
		EIMSK = 0b00110000;
	}
}


ISR(TIMER1_COMPA_vect){
	                                                                                                                                          
	switch(MotorMode){
		case 0:
			PORTA = 0b00000000;
		break;
		case 1:
			if(PINA == 0b00000001){
				PORTA = 0b00000000;
			}else{
				PORTA = 0b00000001;
			}
		break;
		case 2:
			if(PINA == 0b00000010){
				PORTA = 0b00000000;
				}else{
				PORTA = 0b00000010;
			}
		break;
			
	}
	
}

ISR(TIMER3_COMPA_vect){
	
	bLightToggle();
}


int main(void)
{
	sei();
	initCounter();
	initMotor();
	InitUART(9600, 8, 0);
	InitUARTnul(9600);
	bLightInit();
	counter = 0;
	PORTA = 0b00000000;
	TIMSK3 = 0b00000000;

	
	while(1){
		
		
		SendInteger(counter);		
		switch(counter){
			case 1:   // Start manuelt med brik
			if(newCount){
				playStartSound();
				TIMSK3 = 0b00000010;
				TCNT3 = 0;
				bLightStrength(15);
				newCount = false;
				_delay_ms(3000); //Delay for at spille intro 10 sek
				_delay_ms(50);
				fLightOn();
				_delay_ms(20);
				MotorMode = 1;
				_delay_ms(100);
				TCNT1 = 0;
				setSpeed(99.0);
				counter = 1;
			}
			
			
			break;
			
			case 2:  // 1. brik
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound();
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 2;
			}
			
			break;
			
			case 3:   // 2. brik
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 3;
			}
		
			
			break;
			
			case 4:   // 3. brik på bakken
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 4;
			}
			break;
			
			case 5:  // 4. brik
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 5;
			}
			
			break;
			
			case 6:  // 5. brik
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(90);
				_delay_ms(150);
				counter = 6;
			}
			
			break;
			
			case 7: // stop ved 6. brik
			if(newCount){
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				MotorMode = 2;
				TCNT1 = 0;
				setSpeed(99.0);
				TCNT3 = 0;
				bLightStrength(254);
				counter = 7;
				_delay_ms(500);
				TCNT3 = 0;
				bLightStrength(15);
			}
			
			break;
			
			case 8: // tilbage forbi 6. brik
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 8;
			}
			
			break;
			
			case 9:
			
			counter++;
			break;
			
			case 10: //Stop ved 5. brik igen
			if(newCount){
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT3 = 0;
				bLightStrength(254);
				MotorMode = 1;
				_delay_ms(100);
				TCNT1 = 0;
				setSpeed(99.0);
				counter = 10;
				_delay_ms(500);
				TCNT3 = 0;
				bLightStrength(15);
		
			}
			break;
			
			case 11: // 5. brik igen
			if(newCount){
				TCNT3 = 0;
				bLightStrength(15);
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				MotorMode = 1;
				_delay_ms(100);
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(500);
				counter = 11;
			}
			break;
			
			case 12: // 6. brik igen 
			if(newCount){
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				setSpeed(0);
				MotorMode = 0;
				TCNT3 = 0;
				bLightStrength(254);
				_delay_ms(500);
				TCNT3 = 0;
				bLightStrength(15);
				_delay_ms(400);
				MotorMode = 1;
				_delay_ms(100);
				TCNT1 = 0;
				setSpeed(99.0);
				counter = 12;
			}
			
			break;
			
			case 13: // Stop efter 7. brik
			if(newCount){
				playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				_delay_ms(1000);
				TCNT3 = 0;
				bLightStrength(254);
				MotorMode = 0;
				_delay_ms(500);
				fLightOff();
				TIMSK3 = 0b00000000;
				PORTC = 0b00000000;
				playEndSound(); //Mario end
			}
			
			break;
		}
			
	}
	
}
