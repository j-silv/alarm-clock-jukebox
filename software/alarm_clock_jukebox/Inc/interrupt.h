#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H


// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include <sys/alt_irq.h>

#define ISR_REGISTRATION_SUCCESS 0
#define ISR_REGISTRATION_FAILURE 1

int registerISR(void);
void enableTimerSecondISR(void);
void timerSecondISR(void* isr_context);
int registerTimerSecondISR(void);

// callbacks in main.c
void timerSecondCallback(void);

#endif