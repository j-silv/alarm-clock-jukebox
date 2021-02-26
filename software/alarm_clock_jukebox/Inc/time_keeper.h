#ifndef __TIME_H
#define __TIME_H

// C libraries
#include <stdint.h>


// API
void resetClockTime(void);
void resetAlarmTime(void);

struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

struct time updateTime(uint8_t time_type, uint8_t time_unit, uint8_t operation, uint8_t carry_setting);

#define ONE_HOUR 60
#define ONE_MINUTE 60
#define SECOND 0
#define MINUTE 1
#define HOUR 2
#define UP 3
#define DOWN 4
#define CLOCK 5
#define ALARM 6
#define CARRY_ON 7
#define CARRY_OFF 8

void incrementClock(uint8_t time_unit, uint8_t carry_setting);
void incrementClockSecond(uint8_t carry_setting);
void incrementClockMinute(uint8_t carry_setting);
void incrementClockHour(void);

void decrementClock(uint8_t time_unit, uint8_t carry_setting);
void decrementClockSecond(uint8_t carry_setting);
void decrementClockMinute(uint8_t carry_setting);
void decrementClockHour(void);

void incrementAlarm(uint8_t time_unit);
void incrementAlarmMinute();
void incrementAlarmHour(void);

void decrementAlarm(uint8_t time_unit);
void decrementAlarmMinute();
void decrementAlarmHour(void);

#endif
