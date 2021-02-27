#include "time_keeper.h"

// define 2 time structs for the clock time and the alarm time
struct time clock;
struct time alarm;

// 24 hour or 12 hour format (24 by default)
volatile uint8_t time_format = 24;


/* ------------------------ CLOCK functions ---------------------- */

// initialize clock time to default time (see display.h)
void resetClockTime(void) {
  clock.hour = reset_clock_value[0];
  clock.minute = reset_clock_value[1];
  clock.second = reset_clock_value[2];
}

struct time getClockTime(void) {
  return clock;
}

/*--------- up operations -------*/

// SECONDS
struct time upClockSecond(uint8_t carry_setting) {
  if (clock.second == (ONE_MINUTE-1)) {
    clock.second = 0;
    
    if (carry_setting == CARRY_ON) {
      upClockMinute(CARRY_ON);
    }
  }
  else {
    clock.second++;
  }
  return clock;
}

// MINUTES
struct time upClockMinute(uint8_t carry_setting) {
  if (clock.minute == (ONE_HOUR-1)) {
    clock.minute = 0;
    
    if (carry_setting == CARRY_ON) {
      upClockHour();
    }
  }
  else {
    clock.minute++;
  }
  return clock;
}

// HOURS
struct time upClockHour(void) {
  if (clock.hour == (time_format-1)) {
    clock.hour = 0;
  }
  else {
    clock.hour++;
  }
  return clock;
}

/*--------- down operations -------*/

// SECONDS
struct time downClockSecond(uint8_t carry_setting) {
  if (clock.second == 0) {
    clock.second = (ONE_MINUTE-1);
    
    if (carry_setting == CARRY_ON) {
      downClockMinute(CARRY_ON);
    }
  }
  else {
    clock.second--;
  }
  return clock;
}

// MINUTES
struct time downClockMinute(uint8_t carry_setting) {
  if (clock.minute == 0) {
    clock.minute = (ONE_HOUR-1);
    
    if (carry_setting == CARRY_ON) {
      downClockHour();
    }
  }
  else {
    clock.minute--;
  }
  return clock;
}

// HOURS
struct time downClockHour(void) {
  if (clock.hour == 0) {
    clock.hour = (time_format-1);
  }
  else {
    clock.hour--;
  }
  return clock;
}


/* ------------------------ ALARM functions ---------------------- */

// initialize alarm time to 00:00 (seconds are turned off)
void resetAlarmTime(void) {
  // necessary to cast to a time struct, otherwise the 
  // value assignment won't work
  alarm =  (struct time){0};

  // we explicitly request that the seconds are not displayed
  alarm.second = DONT_DISPLAY;
}

struct time getAlarmTime(void) {
  return alarm;
}

/*--------- up operations -------*/

// MINUTES
struct time upAlarmMinute(void) {
  if (alarm.minute == (ONE_HOUR-1)) {
    alarm.minute = 0;
  }
  else {
    alarm.minute++;
  }
  return alarm;
}

// HOURS
struct time upAlarmHour(void) {
  if (alarm.hour == (time_format-1)) {
    alarm.hour = 0;
  }
  else {
    alarm.hour++;
  }
  return alarm;
}

/*--------- down operations -------*/

// MINUTES
struct time downAlarmMinute(void) {
  if (alarm.minute == 0) {
    alarm.minute = (ONE_HOUR-1);
  }
  else {
    alarm.minute--;
  }
  return alarm;
}

// HOURS
struct time downAlarmHour(void) {
  if (alarm.hour == 0) {
    alarm.hour = (time_format-1);
  }
  else {
    alarm.hour--;
  }
  return alarm;
}
