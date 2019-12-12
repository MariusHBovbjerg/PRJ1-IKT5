/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#pragma once

void initMotor(); // Function for init PWM timer for motor.

void forward(char); // Function for driving forward.

void reverse(char); // Function for driving in reverse.

void stopMotor(char); // Function for driving in reverse.

void setSpeed(char); // Function to set the speed of the car.