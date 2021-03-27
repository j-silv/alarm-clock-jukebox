#ifndef __PWM_H
#define __PWM_H

// C libraries
#include <stdint.h>
#include "altera_avalon_pwm_regs.h"
#include "altera_avalon_pwm_routines.h"
#include "system.h"
#include <stdio.h>

#define NIOS_CLOCK_FREQ 50000000
#define MAX_VOLUME 12

uint8_t getVolume(void);
uint8_t upVolume(void);
uint8_t downVolume(void);
void print_error(unsigned int address, int return_code);
void check_return_code(unsigned int address, int return_code);
void testPWM(void);
void default500HzSquareWave(void);
void stopPWM(void);
void writePWM(int frequency);

// follows an exponential curve
const uint8_t duty_cycle_lookup_table[MAX_VOLUME+1] = {
  // min duty cycle 0% -> volume = 0
  0,
  0.00310253,
  0.004924651,
  0.007816907,
  0.012407789,
  0.019694903,
  0.031261751,
  0.049621827,
  0.078764805,
  0.1250235,
  0.19845,
  0.003103,
  // max duty cycle 50% -> volume = 20
  0.5
};

#endif

