#ifndef __MAIN_H
#define __MAIN_H

// macros
#define FALSE 0
#define TRUE 1
#define NOT_ARMED 2
#define ARMED 3
#define TIME_DISPLAY 4
#define ALARM_DISPLAY 5
#define VOLUME_DISPLAY 6
#define SONG_DISPLAY 7

#define SECOND 0
#define MINUTE 1
#define HOUR 2
#define UP 3
#define DOWN 4
#define CLOCK 5
#define ALARM 6
#define CARRY_ON 7
#define CARRY_OFF 8

#define ISR_REGISTRATION_SUCCESS 0
#define ISR_REGISTRATION_FAILURE -1

// C libraries
#include <stdio.h>
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

// ISRs
void timerSecondISR(void *isr_context);

// interrupt.c API
uint8_t timerSecondRegisterISR(void (*timerSecondISR(void *isr_context)));
void timerSecondEnableInterrupt(void);

// led.c API
void alarmLEDoff(void);
void alarmLEDon(void);
void alarmLEDtoggle(void);

// time.c API
void resetClockTime(void);
void resetAlarmTime(void);
struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};
struct time updateTime(uint8_t time_type, uint8_t time_unit, uint8_t operation, uint8_t carry_setting);

// display.c API
void resetDisplay(void);



#endif
