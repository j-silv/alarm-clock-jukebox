#include "main.h"

typedef struct {
  int hour;
  int minute;
  int second;
} time;

time current_time;
time alarm;

// 24 hour or 12 hour format (24 by default)
int time_format = 24;

// initialize time to 00:00:00
void initializeTime(void) {
  // method #1 (possible to do doing struct declaration?)
  // myStruct m = {0};

  // method #2
  // memset(&m, 0, sizeof(myStruct));

  // method #3
  current_time.hour = 0x0;
  current_time.minute = 0x0;
  current_time.second = 0x0;
}

// initialize alarm to 00:00:00
void initializeAlarm(void) {
  alarm.hour = 0x0;
  alarm.minute = 0x0;
  alarm.second = 0x0;
}

void incrementAlarmHour(void) {
  // case where time is at 12:XX:XX or 24:XX:XX
  if(alarm.hour == time_format) {
    // wrap to 00:XX:XX
    alarm.hour = 0;
  }
  else {
    alarm.hour++;
  }
}

void incrementAlarmMinute(void) {
  // case where time is at XX:60:XX
  if(alarm.minute == ONE_HOUR) {
    incrementAlarmHour();
    alarm.minute = 0;
  }
  else {
    alarm.minute++;
  }
}

void incrementTimeHour(void) {
  // case where time is at 12:XX:XX or 24:XX:XX
  if(current_time.hour == time_format) {
    // wrap to 00:XX:XX
    current_time.hour = 0;
  }
  else {
    current_time.hour++;
  }
}

void incrementTimeMinute(void) {
  // case where time is at XX:60:XX
  if(current_time.minute == ONE_HOUR) {
    incrementTimeHour();
    current_time.minute = 0;
  }
  else {
    current_time.minute++;
  }
}

void incrementTimeSecond(void) {
  // case where time is at XX:XX:60
  if(current_time.second == ONE_MINUTE) {
    incrementTimeMinute();
    current_time.second = 0;
  }
  else {
    current_time.second++;
  }
}