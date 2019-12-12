/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "Counter.h"
#include <avr/interrupt.h>


void initCounter(){
	EIMSK = 0b00001100; // INT 2 og INT 3 - BEN 45 og 46 respectively.
	EICRA = 0b11110000; // INT 2 og INT 3 both rising edge.
}