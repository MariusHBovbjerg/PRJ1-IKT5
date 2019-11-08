/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#pragma once

void initMotor(); // Function for init PWM timer for motor.

void forward(); // Function for driving forward.

void reverse(); // Function for driving in reverse.

void setSpeed(int); // Function to set the speed of the car.