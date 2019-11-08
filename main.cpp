/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "includes.h"

volatile unsigned char counter = 0;

ISR(INT2_vect){ //On rising edge, count + 1
	counter++;
}

ISR(INT3_vect){ //On rising edge, count + 1
	counter++;
}


int main(void)
{
    initCounter();
    while (1) 
    {
		
		
    }
}