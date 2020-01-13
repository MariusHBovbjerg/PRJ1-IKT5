/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "FLightDriver.h"

#include <stdio.h>
#include <avr/io.h>

void FlightInit(void){
	DDRG = 0xFF; 
}

void FlightOn(void){
	PORTG = 0b00000101; //ben 39 og 41
}
void FlightOff(void){
	PORTG = 0b00000000;
}