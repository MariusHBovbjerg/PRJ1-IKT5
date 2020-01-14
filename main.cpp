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

int counter = 0;
bool finalSound = true;
bool newCount = true;
bool SensorDelay = true;

unsigned int MotorMode = 0;

ISR(INT4_vect){ //On rising edge, count + 1
	if(SensorDelay){
		newCount = true;
		counter++;
		SensorDelay = false;
	}	
}
ISR(INT5_vect){
	if(SensorDelay){
		newCount = true;
		counter++;
		SensorDelay = false;
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
		
		if(!SensorDelay){
			_delay_ms(100);
			SensorDelay = true;
		}
		
		switch(counter){
			case 0:   // Start manuelt med brik
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				FlightOn();
			}
			blightStrength(50);
			_delay_ms(10000); //Delay for at spille intro 10 sek
			MotorMode = 1;
			setSpeed(150);
			break;
			case 1:  // 1. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			setSpeed(204);
			break;
			case 2:   // 2. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			setSpeed(150);
			
			break;
			case 3:   // 3. brik på bakken
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			
			break;
			case 4:  // 4. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			
			break;
			case 5:  // 5. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			
			break;
			case 6: // stop ved 6. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
				blightStrength(254);
				MotorMode = 2;
				setSpeed(150);
				_delay_ms(300);
			}
			blightStrength(50);
			
			break;
			case 7: // tilbage og stop ved 5. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario coin
			}
			
			break;
			case 8: //5. brik igen
			if(newCount){
				newCount = false;
				playNext(); //Mario Intro
				blightStrength(254);				
				MotorMode = 1;
				_delay_ms(300)
			}
			blightStrength(50);
			break;
			case 9: // 6. brik igen
			if(newCount){
				newCount = false;
				playNext(); //Mario Coin
				MotorMode = 0;
				_delay_ms(1000);
				MotorMode = 1;
			}
			break;
			case 10: //stop efter 7. brik
			if(newCount){
				newCount = false;
				playNext(); //Mario Coin
			}
			break;
			case 11:
			if(newCount){
				newCount = false;
				playNext(); //Mario Coin
				blightStrength(254);

			}
			_delay_ms(200);
			setSpeed(150);
			_delay_ms(200);
			setSpeed(100);
			_delay_ms(200);
			setSpeed(50);
			_delay_ms(200);
			setSpeed(1);
			
			MotorMode = 0;
			FlightOff();
			blightStrength(1);
			if(finalSound){
				finalSound = false;
				playNext(); //Mario end
			}
			
			break;
			default:
			MotorMode = 0;
			setSpeed(0);
			break;
		}
			
	}
	
}
