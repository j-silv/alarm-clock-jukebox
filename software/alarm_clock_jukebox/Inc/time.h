#ifndef __TIME_H
#define __TIME_H

// C libraries
#include <stdint.h>

// API
void resetClockTime(void);
void resetAlarmTime(void);


#define ONE_HOUR 60
#define ONE_MINUTE 60

void resetClockTime(void);
void resetAlarmTime(void);

void incrementAlarmHour(void);
void incrementAlarmMinute(void);
void incrementTimeHour(void);
void incrementTimeMinute(void);
void incrementTimeSecond(void);

#endif
