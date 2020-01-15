/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#define F_CPU 16000000
#include "SoundDriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*************************************************************************
UART 0 initialization:
    Asynchronous mode.
    Baud rate = 9600.
    Data bits = 8.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = 9600.
    Data bits = 8.
*************************************************************************/
void InitUART(unsigned long BAUD, unsigned char DataBit, bool Rx_Int)
{
   if(Rx_Int){
	  UCSR1B = 0b10011000; 
	  sei();
   }else{
	   UCSR1B = 0b00011000;
   }
   if((BAUD >= 300) && (BAUD <= 115200) && (DataBit >= 5) && (DataBit <= 8)){
	   switch(DataBit){
		   case 5:
			   UCSR1C = 0b00000000;
			   break;
		   
		   case 6:
			   UCSR1C = 0b00000010;
			   break;
		   
		   case 7:
			   UCSR1C = 0b00000100;
			   break;
		   
		   case 8:
			   UCSR1C = 0b00000110;
			   break;
		   
		   default:
			   UCSR1C = 0b00000110;
			   break;
	   }
	}
	UBRR1L = ((F_CPU/(16*BAUD))-1);
}

void SendChar(char Tegn)
{
   while(!(UCSR1A & (1<<UDRE1))){
	   
   }
   UDR1 = Tegn;
}

void playNext()
{

	SendChar(0x7E);
	SendChar(0x01);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0xFF);
	SendChar(0xFF);
	SendChar(0xEF);

};

void volumeUp()
{

	SendChar(0x7E);
	SendChar(0x04);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0xFF);
	SendChar(0xFC);
	SendChar(0xEF);

};
