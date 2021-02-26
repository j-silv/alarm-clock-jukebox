#ifndef __MAIN_H
#define __MAIN_H

// macros
#define FALSE 0
#define TRUE 1
#define NOT_ARMED 2
#define ARMED 3
#define CLOCK_DISPLAY 4
#define ALARM_DISPLAY 5
#define VOLUME_DISPLAY 6
#define SONG_DISPLAY 7

#define CARRY_ON 0
#define CARRY_OFF 1
#define SECOND 2
#define MINUTE 3
#define HOUR 4
#define UP 5
#define DOWN 6
#define CLOCK 7
#define ALARM 8

#define ISR_REGISTRATION_SUCCESS 0
#define ISR_REGISTRATION_FAILURE 1

// C libraries
#include <stdio.h>
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"

// structs
struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

struct config {
  uint8_t on;
  uint8_t hour;
  uint8_t minute;
};
struct mode{
  uint8_t invalid;
  uint8_t display;
  uint8_t alarm;
  struct config config;
};

// ISRs
void timerSecondISR(void *isr_context);
void switchesISR(void *isr_context);

// interrupt.c API
uint8_t timerSecondRegisterISR(void (*timerSecondISR)(void *isr_context));
void timerSecondEnableInterrupt(void);
uint8_t switchesRegisterISR(void (*switchesISR)(void *isr_context));
void switchesEnableInterrupt(void);

// led.c API
void alarmLEDoff(void);
void alarmLEDon(void);
void alarmLEDtoggle(void);

// time.c API
void resetClockTime(void);
void resetAlarmTime(void);
struct time upClockSecond(uint8_t carry_setting);
struct time upClockMinute(uint8_t carry_setting);
struct time upClockHour(void);
struct time downClockSecond(uint8_t carry_setting);
struct time downClockMinute(uint8_t carry_setting);
struct time downClockHour(void);
struct time upAlarmMinute();
struct time upAlarmHour(void);
struct time downAlarmMinute();
struct time downAlarmHour(void);

// display.c API
void resetDisplay(void);
void updateDisplay(struct time time);

// switches.c API
struct mode determineMode(void);



#endif
