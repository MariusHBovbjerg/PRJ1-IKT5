/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */
 
#pragma once

void InitUART(unsigned long, unsigned char, bool);
bool CharReady();
char ReadChar();
void SendChar(char);
void SendString(char*);
void SendInteger(int);