/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
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
	newCount = true;
	counter++;
	EIMSK = 0b00000000;
	_delay_ms(300);
	EIFR = 0b00110000;
	EIMSK = 0b00110000;
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
	newCount = true;
	counter++;
	EIMSK = 0b00000000;
	_delay_ms(300);
	EIFR = 0b00110000;
	EIMSK = 0b00110000;
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
	bLightStrength(1);
	volumeUp();
	volumeUp();
	volumeUp();
	volumeUp();
	counter = 0;
	PORTA = 0b00000000;
	while(1){
		
		SendInteger(counter);		
		switch(counter){
			case 1:   // Start manuelt med brik
			if(newCount){
				newCount = false;
				playNext();
				//playStartSound(); //Mario Intro
				fLightOn();
				bLightStrength(50);
				_delay_ms(1500); //Delay for at spille intro 10 sek
				MotorMode = 1;
				_delay_ms(50);
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 1;
			}
			
			MotorMode = 1;
			break;
			
			case 2:  // 1. brik
			if(newCount){
				//stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
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
				playNext();
				//playCoinSound(); //Mario coin
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
				/*//stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(80.0);
				_delay_ms(150);*/
				playNext();
				//playCoinSound(); //Mario coin
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
				//stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
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
				stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
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
				stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				MotorMode = 2;
				TCNT1 = 0;
				setSpeed(99.0);
				bLightStrength(254);
				counter = 7;
				_delay_ms(500);
				bLightStrength(50);
			}
			
			break;
			
			case 8: // tilbage forbi 6. brik
			if(newCount){
				stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				TCNT1 = 0;
				setSpeed(99.0);
				_delay_ms(150);
				counter = 8;
			}
			
			break;
			
			case 9:
			//if(newCount){
				//stopSOMO();
				//playCoinSound(); //Mario coin
				//_delay_ms(10);
				//newCount = false;
				//
				//TCNT1 = 0;
				//setSpeed(99);
			//}
			playNext();
			counter++;
			break;
			
			case 10: //Stop ved 5. brik igen
			if(newCount){
				//stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				bLightStrength(254);
				MotorMode = 1;
				_delay_ms(10);
				TCNT1 = 0;
				setSpeed(99.0);
				counter = 10;
				_delay_ms(500);
				bLightStrength(50);
		
			}
			break;
			
			case 11: // 5. brik igen
			if(newCount){
				stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				MotorMode = 1;
				TCNT1 = 0;
				setSpeed(75.0);
				_delay_ms(200);
				counter = 11;
			}
			break;
			
			case 12: // 6. brik igen 
			if(newCount){
				stopSOMO();
				playNext();
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				setSpeed(0);
				MotorMode = 0;
				_delay_ms(2000);
				MotorMode = 1;
				TCNT1 = 0;
				setSpeed(99.0);
				counter = 12;
			}
			
			break;
			
			case 13: // Stop efter 7. brik
			if(newCount){
				stopSOMO();
				
				//playCoinSound(); //Mario coin
				_delay_ms(10);
				newCount = false;
				bLightStrength(254);
				_delay_ms(1000);
				MotorMode = 0;
				_delay_ms(500);
				fLightOff();
				bLightStrength(1);
				stopSOMO();
				//playEndSound(); //Mario end
				playNext();
			}
			
			break;
		}
			
	}
	
}
