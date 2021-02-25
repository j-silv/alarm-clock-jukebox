#ifndef __MAIN_H
#define __MAIN_H

#define ISR_REGISTRATION_SUCCESS 0
#define ISR_REGISTRATION_FAILURE 1

// C libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include <sys/alt_irq.h>

// interrupt callbacks
void timerSecondCallback(void);

// interrupt.c API
uint8_t registerISR(void);
void enableTimerSecondISR(void);

// led.c API
void alarmLEDoff(void);
void alarmLEDon(void);
void alarmLEDtoggle(void);

// constants
#define TIME_DISPLAY 0
#define NOT_ARMED 0
#define FALSE 0
#define TRUE 1



#endif
