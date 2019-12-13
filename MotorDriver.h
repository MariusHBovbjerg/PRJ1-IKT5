/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#pragma once

void initMotor(); // Function for init PWM timer for motor.

void forwardMotor(int); // Function for driving forward.

void reverseMotor(int); // Function for driving in reverse.

void stopMotor(int); // Function for driving in reverse.

void setSpeed(int); // Function to set the speed of the car.