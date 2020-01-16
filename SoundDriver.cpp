/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Emil Engstrøm & Kean Væring Hansen
 */ 

#define F_CPU 16000000
#include "SoundDriver.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void InitUART(unsigned long BAUD, unsigned char DataBit, bool Rx_Int)
{
   if(Rx_Int){
	  UCSR2B = 0b10011000; 
	  sei();
   }else{
	   UCSR2B = 0b00011000;
   }
   if((BAUD >= 300) && (BAUD <= 115200) && (DataBit >= 5) && (DataBit <= 8)){
	   switch(DataBit){
		   case 5:
			   UCSR2C = 0b00000000;
			   break;
		   
		   case 6:
			   UCSR2C = 0b00000010;
			   break;
		   
		   case 7:
			   UCSR2C = 0b00000100;
			   break;
		   
		   case 8:
			   UCSR2C = 0b00000110;
			   break;
		   
		   default:
			   UCSR2C = 0b00000110;
			   break;
	   }
	}
	UBRR2L = ((F_CPU/(16*BAUD))-1);
	volumeMax();
}

void SendChar(char Tegn)
{
   while(!(UCSR2A & (1<<UDRE2))){
	   
   }
   UDR2 = Tegn;
}

void playCoinSound()
{
	SendChar(0x7E);
	SendChar(0x0F);
	SendChar(0x00);
	SendChar(0x03);
	SendChar(0x01);
	SendChar(0xFF);
	SendChar(0xEF);
	SendChar(0xEF);

};

void playStartSound()
{
	SendChar(0x7E);
	SendChar(0x0F);
	SendChar(0x00);
	SendChar(0x01);
	SendChar(0x01);
	SendChar(0xFF);
	SendChar(0xEF);
	SendChar(0xEF);

};

void playEndSound()
{
	SendChar(0x7E);
	SendChar(0x0F);
	SendChar(0x00);
	SendChar(0x02);
	SendChar(0x01);
	SendChar(0xFF);
	SendChar(0xEF);
	SendChar(0xEF);

};

void volumeMax()
{

	SendChar(0x7E);
	SendChar(0x06);
	SendChar(0x00);
	SendChar(0x00);
	SendChar(0x1E);
	SendChar(0xFF);
	SendChar(0xDC);
	SendChar(0xEF);

};

