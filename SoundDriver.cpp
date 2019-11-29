/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#include "SoundDriver.h"
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
	  UCSR0B = 0b10011000; 
	  sei();
   }else{
	   UCSR0B = 0b00011000;
   }
   if((BAUD >= 300) && (BAUD <= 115200) && (DataBit >= 5) && (DataBit <= 8)){
	   switch(DataBit){
		   case 5:
			   UCSR0C = 0b00000000;
			   break;
		   
		   case 6:
			   UCSR0C = 0b00000010;
			   break;
		   
		   case 7:
			   UCSR0C = 0b00000100;
			   break;
		   
		   case 8:
			   UCSR0C = 0b00000110;
			   break;
		   
		   default:
			   UCSR0C = 0b00000110;
			   break;
	   }
	}
	UBRR0L = ((F_CPU/(16*BAUD))-1);
}

/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
bool CharReady()
{
   return (UCSR0A & (1<<TXC0)) ? true : false;
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
   while(!(UCSR0A & (1<<RXC0))){
	   
   }
   return UDR0;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
   while(!(UCSR0A & (1<<UDRE0))){
	   
   }
   UDR0 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
	while(*Streng != '\0'){
		SendChar(*Streng);
		Streng++;
	}
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
   char intStr[30];
   itoa(Tal, intStr, 10);
   SendString(intStr);
}


/************************************************************************/