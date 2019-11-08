/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "includes.h"

void setSpeed(int speed) {
	char dutyCycle;
	if (speed > 100) {
		char dutyCycle = 100;
	}
	else {
		char dutyCycle = speed;
	}

	//set duty cycle
}