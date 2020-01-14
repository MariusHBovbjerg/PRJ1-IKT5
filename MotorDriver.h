/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#pragma once

void initMotor(); // Function for init PWM timer for motor.

void forwardMotor(unsigned int); // Function for driving forward.

void reverseMotor(unsigned int); // Function for driving in reverse.

void stopMotor(unsigned int); // Function for driving in reverse.

void setSpeed(int); // Function to set the speed of the car.