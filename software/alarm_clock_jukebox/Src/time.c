#include "time.h"

typedef struct {
  volatile uint8_t hour;
  volatile uint8_t minute;
  volatile uint8_t second;
} time_struct;

time_struct clock_time;
time_struct alarm_time;

// 24 hour or 12 hour format (24 by default)
volatile uint8_t time_format = 24;

// initialize clock time to 00:00:00
void resetClockTime(void) {
  clock_time = (time_struct){0};
}

// initialize alarm time to 00:00:00
void resetAlarmTime(void) {
  alarm_time = (time_struct){0};
}

/*
void incrementAlarmHour(void) {
  // case where time is at 12:XX:XX or 24:XX:XX
  if(alarm_time.hour == time_format) {
    // wrap to 00:XX:XX
    alarm_time.hour = 0;
  }
  else {
    alarm_time.hour++;
  }
}

void incrementAlarmMinute(void) {
  // case where time is at XX:60:XX
  if(alarm_time.minute == ONE_HOUR) {
    incrementAlarmHour();
    alarm_time.minute = 0;
  }
  else {
    alarm_time.minute++;
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
*/