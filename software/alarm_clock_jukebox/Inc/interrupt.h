#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

// C libraries
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include <sys/alt_irq.h>

uint8_t timerSecondRegisterISR(void (*timerSecondISR)(void *isr_context));
void timerSecondEnableInterrupt(void);

uint8_t buttonsRegisterISR(void (*buttonsISR)(void *isr_context));
void buttonsEnableInterrupt(void);

uint8_t switchesRegisterISR(void (*switchesISR)(void *isr_context));
void switchesEnableInterrupt(void);

uint8_t timerPWMRegisterISR(void (*timerPWMISR)(void *isr_context));
void timerPWMEnableInterrupt(int timeout);
void timerPWMDisableInterrupt(void);

#define SWITCHES_INTERRUPT_MASK 0xFFFF
#define BUTTONS_INTERRUPT_MASK 0x3
#define AVALON_TIMER_PERIOD_WIDTH 16

#define NIOS_CLOCK_FREQ 50000000

#endif