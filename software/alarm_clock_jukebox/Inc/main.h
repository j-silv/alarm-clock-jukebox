#ifndef __MAIN_H
#define __MAIN_H

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

struct note_info {
  int frequency;
  int duration;
  int endofsong;
};

// macros
// values possible for the mode struct members

// mode.invalid = {FALSE, TRUE}
// mode.config.on = {FALSE, TRUE}
// mode.config.hour = {FALSE, TRUE}
// mode.config.minute = {FALSE, TRUE}
#define FALSE 0 
#define TRUE 1

// mode.alarm = {OFF, ON}
#define OFF 0
#define ON 1

// mode.display = {DISP_CLOCK, DISP_ALARM, DISP_VOLUME, DISP_SONG}
#define DISP_CLOCK 0
#define DISP_ALARM 1
#define DISP_VOLUME 2
#define DISP_SONG 3

#define CARRY_OFF 0
#define CARRY_ON 1

/* the button values that correspond to the requested operations
-if the button state = 1, then the down button was pressed
-if the button state = 2, then the up button was pressed
-if both buttons were pressed (state = 3), then a reset operation was requested  */
#define DOWN 1
#define UP 2
#define RESET 3

#define ISR_REGISTRATION_SUCCESS 0
#define ISR_REGISTRATION_FAILURE 1

/* this is a macro for the time struct, which will explicitly let the display module know to
not display the digits for a particular time unit (for example, in alarm config mode, we don't
want to show the seconds time unit). */
#define DONT_DISPLAY 100


// ISRs
void timerSecondISR(void *isr_context);
void switchesISR(void *isr_context);
void buttonsISR(void *isr_context);
void timerPWMISR(void *isr_context);


// interrupt.c API

uint8_t timerSecondRegisterISR(void (*timerSecondISR)(void *isr_context));
void timerSecondEnableInterrupt(void);

uint8_t buttonsRegisterISR(void (*buttonsISR)(void *isr_context));
void buttonsEnableInterrupt(void);

uint8_t switchesRegisterISR(void (*switchesISR)(void *isr_context));
void switchesEnableInterrupt(void);

uint8_t timerPWMRegisterISR(void (*timerPWMISR)(void *isr_context));
void timerPWMEnableInterrupt(int timeout);
void timerPWMDisableInterrupt(void);

// led.c API
void alarmLEDoff(void);
void alarmLEDon(void);
void alarmLEDtoggle(void);

// time_keeper.c API
void resetClockTime(void);
void resetAlarmTime(void);
struct time getClockTime(void);
struct time getAlarmTime(void);
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

// rtttl.c API
uint8_t getSong(void);
uint8_t upSong(void);
uint8_t downSong(void);
struct note_info playSong(void);
struct note_info getNote(void);

// pwm.c API
uint8_t getVolume(void);
uint8_t upVolume(void);
uint8_t downVolume(void);
void default500HzSquareWave(void);
void testPWM(void);
void stopPWM(void);
void writePWM(int frequency);


#endif
