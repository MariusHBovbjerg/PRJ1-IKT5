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
#include "Sensor.h"
#include "SoundDriver.h"
#include "BLightDriver.h"

volatile int counter = 0;
bool finalSound = true;
bool newCount = true;

unsigned int MotorMode = 0;

ISR(INT4_vect){ //On rising edge, count + 1
	newCount = true;
	counter++;
	_delay_ms(200);
	EIFR = 0b00100000;
}
ISR(INT5_vect){
	newCount = true;
	counter++;
	_delay_ms(200);
	EIFR = 0b00010000;
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
	initCounter();
	initMotor();
	InitUART(9600, 8, 0);
	BlightInit();
	blightStrength(1);
	volumeUp();
	volumeUp();
	volumeUp();
	volumeUp();
	counter = 0;
	MotorMode = 0;
	PORTA = 0b00000000;
	while(1){
		
		switch(counter){
			case 1:   // Start manuelt med brik
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				FlightOn();
				_delay_ms(2000); //Delay for at spille intro 10 sek
				blightStrength(50);
			}
			MotorMode = 1;
			setSpeed(150);
			break;
			
			case 2:  // 1. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
			}
			setSpeed(200);
			
			break;
			case 3:   // 2. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
			}
			setSpeed(254);
			
			
			break;
			case 4:   // 3. brik på bakken
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
			}
			setSpeed(100);
			break;
			
			case 5:  // 4. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				
			}
			setSpeed(150);
			break;
			
			case 6:  // 5. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				
			}
			setSpeed(150);
			break;
			
			case 7: // stop ved 6. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				MotorMode = 2;
				_delay_ms(10);
				setSpeed(150);
				blightStrength(254);
				_delay_ms(500);
				blightStrength(50);
			}
			
			
			break;
			case 8: // tilbage og stop ved 5. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				
			}
			setSpeed(200);
			break;
			case 9: //5. brik igen
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				blightStrength(254);		
				MotorMode = 1;
				_delay_ms(10);
				setSpeed(150);
				_delay_ms(500);
				blightStrength(50);
		
			}
			
			break;
			case 10: // 6. brik igen
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				MotorMode = 0;
				_delay_ms(1500);
				MotorMode = 1;
			}
			break;
			case 11: //stop efter 7. brik
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
			}
			break;
			case 12:
			if(newCount){
				playNext(); //Mario coin
				newCount = false;
				blightStrength(254);
				_delay_ms(350);
				setSpeed(100);
				_delay_ms(350);
				setSpeed(50);
				_delay_ms(350);

			}
			setSpeed(1);
			MotorMode = 0;
			_delay_ms(500);
			FlightOff();
			blightStrength(1);
			if(finalSound){
				finalSound = false;
				playNext(); //Mario end
			}
			
			break;
			default:
			MotorMode = 0;
			break;
		}
			
	}
	
}
