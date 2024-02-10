/*
 * global.h
 *
 * Created: 01.12.2023 0:31:59
 *  Author: mistp
 */ 


#ifndef GLOBAL_H_
#define GLOBAL_H_


#define F_CPU 28 * 1000000UL

#define NOP asm("nop")

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#define Sleep(x) _delay_ms(x)

#include "ili9341.h"


#endif /* GLOBAL_H_ */