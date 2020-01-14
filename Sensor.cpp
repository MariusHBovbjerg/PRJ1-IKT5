/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "Sensor.h"
#include <avr/interrupt.h>


void initCounter(int var){
	EIMSK = 0b00110000; // INT 4 & INT 5 active - BEN 2.
	EICRB = 0b00001111; // INT 4 & INT 5 rising edge.
	var = 0;
}