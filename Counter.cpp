/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "Counter.h"
#include <avr/interrupt.h>


void initCounter(int var){
	EIMSK = 0b00010000; // INT 4 active - BEN 2.
	EICRB = 0b00000011; // INT 4 rising edge.
	var = 0;
}