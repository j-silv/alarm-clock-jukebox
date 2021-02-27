#ifndef __PWM_H
#define __PWM_H

// C libraries
#include <stdint.h>
#include "altera_avalon_pwm_regs.h"
#include "altera_avalon_pwm_routines.h"
#include "system.h"
#include <stdio.h>

uint8_t getVolume(void);
uint8_t upVolume(void);
uint8_t downVolume(void);
void print_error(unsigned int address, int return_code);
void check_return_code(unsigned int address, int return_code);
void testPWM(void);
void default500HzSquareWave(void);

#endif

