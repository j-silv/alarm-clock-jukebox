#ifndef __TIME_KEEPER_H
#define __TIME_KEEPER_H

// C libraries
#include <stdint.h>


// API
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
struct time upAlarmMinute(void);
struct time upAlarmHour(void);
struct time downAlarmMinute(void);
struct time downAlarmHour(void);

struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};


#define ONE_HOUR 60
#define ONE_MINUTE 60
#define CARRY_OFF 0
#define CARRY_ON 1

/* this is a macro for the time struct, which will explicitly let the display module know to
not display the digits for a particular time unit (for example, in alarm config mode, we don't
want to show the seconds time unit). */
#define DONT_DISPLAY 100

/* default time that the clock is set to is used for debugging purposes (carry tests)
... however in theory it could be set to the computer's current time at programming time 
with some C magic */
const uint8_t reset_clock_value [] = {
  11, // hour
  59, // minute
  0   // second
};



#endif
