#ifndef __TIME_H
#define __TIME_H

// C libraries
#include <stdint.h>


// API
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

struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};


#define ONE_HOUR 60
#define ONE_MINUTE 60
#define CARRY_ON 0
#define CARRY_OFF 1



#endif
