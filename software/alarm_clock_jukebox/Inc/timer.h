/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

#define ONE_HOUR 60
#define ONE_MINUTE 60

void initializeTime(void);
void initializeAlarm(void);

void incrementAlarmHour(void);
void incrementAlarmMinute(void);

void incrementTimeHour(void);
void incrementTimeMinute(void);
void incrementTimeSecond(void);

#endif
