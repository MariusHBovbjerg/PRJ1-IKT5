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
#include "MotorDriver.h"
#include "FLightDriver.h"
#include "Counter.h"
#include "SoundDriver.h"
#include "BLightDriver.h"

int counter = 0;
bool finalSound = true;
bool newCount = true;

unsigned int MotorMode = 0;

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
		default:
			PORTA = 0b00000000;
		break;
			
	}
}

ISR(TIMER3_COMPA_vect){
	
	BlightToggle();
}

int main(void)
{
	sei();
	initCounter(counter);
	initMotor();
	InitUART(9600, 8, 0);
	BlightInit();
	blightStrength(1);
	volumeUp();
	volumeUp();
	volumeUp();
	volumeUp();
	counter = -1;
	MotorMode = 0;
	PORTA = 0b00000000;
	while(1){
		
		switch(counter){
			case 0:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				FlightOn();
			}
			blightStrength(50);
			_delay_ms(100); //Delay for at spille intro 10 sek
			MotorMode = 1;
			setSpeed(50);
			break;
			case 1:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			setSpeed(100);
			break;
			case 2:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			setSpeed(150);
			
			break;
			case 3:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			setSpeed(204);
			
			break;
			case 4:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			
			break;
			case 5:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			setSpeed(100);
			MotorMode = 1;
			blightStrength(254);
			
			break;
			case 6:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
			}
			setSpeed(150);
			
			break;
			case 7:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				blightStrength(254);
			}
			MotorMode = 2;
			_delay_ms(300); // Ændre hvis lyset slukker før bilen stopper med at bremse.
			blightStrength(50);
			
			break;
			case 8:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				blightStrength(254);
			}
			MotorMode = 1;
			_delay_ms(300); // Ændre hvis lyset slukker før bilen stopper med at bremse.
			blightStrength(50);
			break;
			case 9:
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				blightStrength(254);
			}
			_delay_ms(100);
			setSpeed(150);
			_delay_ms(100);
			setSpeed(100);
			_delay_ms(100);
			setSpeed(50);
			_delay_ms(100);
			setSpeed(1);
			
			MotorMode = 0;
			FlightOff();
			blightStrength(1);
			if(finalSound){
				finalSound = false;
				playNext(); //Mario Intro
			}
			
			break;
			default:
			MotorMode = 0;
			setSpeed(0);
			break;
		}
			
	}
	
}
