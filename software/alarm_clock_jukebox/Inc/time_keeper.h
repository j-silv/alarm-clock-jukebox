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

/* if one of the time struct members has 110 as its value, then 
the corresponding digit will give a BCD value of 11 for the decimal
place digit and 10 for the ones place. the COM_ANODE_SEG[] array
will then access indexes 11 and 10, which are 0xFF and turn off the digits */
#define DIGITS_OFF 110

const uint8_t reset_clock_value [] = {
  23, // hour
  59, // minute
  0   // second
};



#endif
