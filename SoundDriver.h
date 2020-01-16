/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Emil Engstrøm & Kean Væring Hansen
 */
 
#pragma once

void InitUART(unsigned long, unsigned char, bool);
void SendChar(char);
void playNext(void);
void volumeUp(void);
void playCoinSound(void);
void playStartSound(void);
void playEndSound(void);
void stopSOMO(void);