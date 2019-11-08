/*
 * PRJ1-IKT5
 *
 * Created: 08/11/2019 11.18.27
 * Author : Marius Hambro Bovbjerg
 */ 

#pragma once

// public libraries
#define F_CPU 16000000
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// proprietary libraries
#include "MotorDriver.h"
#include "FLightDriver.h"
#include "Counter.h"
#include "SoundDriver.h"
#include "BLightDriver.h"