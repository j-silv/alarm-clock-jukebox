#include "time_keeper.h"

// define 2 time structs for the clock time and the alarm time
struct time clock;
struct time alarm;

// 24 hour or 12 hour format (24 by default)
volatile uint8_t time_format = 24;

// initialize clock time to 00:00:00
void resetClockTime(void) {
  // necessary to cast to a time struct, otherwise the 
  // value assignment won't work
  clock = (struct time){0};
}

// initialize alarm time to 00:00:00
void resetAlarmTime(void) {
  alarm =  (struct time){0};
}

/* in this function we determine which time struct to update and whether
or not it's a incrementation of time (+) or a decrementation of time (-) */
struct time updateTime(uint8_t time_type, uint8_t time_unit, uint8_t operation, uint8_t carry_setting) {
  if (time_type == CLOCK) {
    if (operation == UP) {
      incrementClock(time_unit, carry_setting);
    }
    else if (operation == DOWN) {
      decrementClock(time_unit, carry_setting);
    }
    return clock;
  }

  else if (time_type == ALARM) {
    if (operation == UP) {
      incrementAlarm(time_unit);
    }
    else if (operation == DOWN) {
      decrementAlarm(time_unit);
    }
    return alarm;
  }

  // error from main.c call
  else {
    return (struct time){1};
  }
}



/* ------------------------ CLOCK functions ---------------------- */

/*--------- increment operations -------*/

void incrementClock(uint8_t time_unit, uint8_t carry_setting) {
  switch (time_unit) {
    case SECOND:
      incrementClockSecond(carry_setting);
      break;
    case MINUTE:
      incrementClockMinute(carry_setting);
      break;
    case HOUR:
      incrementClockHour();
      break;   
  }
}

// SECONDS
void incrementClockSecond(uint8_t carry_setting) {
  if (clock.second == (ONE_MINUTE-1)) {
    clock.second = 0;
    
    if (carry_setting == CARRY_ON) {
      incrementClockMinute(CARRY_ON);
    }
  }
  else {
    clock.second++;
  }
}

// MINUTES
void incrementClockMinute(uint8_t carry_setting) {
  if (clock.minute == (ONE_HOUR-1)) {
    clock.minute = 0;
    
    if (carry_setting == CARRY_ON) {
      incrementClockHour();
    }
  }
  else {
    clock.minute++;
  }
}

// HOURS
void incrementClockHour(void) {
  if (clock.hour == time_format) {
    clock.hour = 0;
  }
  else {
    clock.hour++;
  }
}

/*--------- decrement operations -------*/

void decrementClock(uint8_t time_unit, uint8_t carry_setting) {
  switch (time_unit) {
    case SECOND:
      decrementClockSecond(carry_setting);
      break;
    case MINUTE:
      decrementClockMinute(carry_setting);
      break;
    case HOUR:
      decrementClockHour();
      break;   
  }
}

// SECONDS
void decrementClockSecond(uint8_t carry_setting) {
  if (clock.second == 0) {
    clock.second = (ONE_MINUTE-1);
    
    if (carry_setting == CARRY_ON) {
      decrementClockMinute(CARRY_ON);
    }
  }
  else {
    clock.second--;
  }
}

// MINUTES
void decrementClockMinute(uint8_t carry_setting) {
  if (clock.minute == 0) {
    clock.minute = (ONE_HOUR-1);
    
    if (carry_setting == CARRY_ON) {
      decrementClockHour();
    }
  }
  else {
    clock.minute--;
  }
}

// HOURS
void decrementClockHour(void) {
  if (clock.hour == 0) {
    clock.hour = time_format;
  }
  else {
    clock.hour--;
  }
}


/* ------------------------ ALARM functions ---------------------- */

/*--------- increment operations -------*/

void incrementAlarm(uint8_t time_unit) {
  switch (time_unit) {
    case MINUTE:
      incrementAlarmMinute();
      break;
    case HOUR:
      incrementAlarmHour();
      break;   
  }
}

// MINUTES
void incrementAlarmMinute() {
  if (alarm.minute == (ONE_HOUR-1)) {
    alarm.minute = 0;
  }
  else {
    alarm.minute++;
  }
}

// HOURS
void incrementAlarmHour(void) {
  if (alarm.hour == time_format) {
    alarm.hour = 0;
  }
  else {
    alarm.hour++;
  }
}

/*--------- decrement operations -------*/

void decrementAlarm(uint8_t time_unit) {
  switch (time_unit) {
    case MINUTE:
      decrementAlarmMinute();
      break;
    case HOUR:
      decrementAlarmHour();
      break;   
  }
}

// MINUTES
void decrementAlarmMinute() {
  if (alarm.minute == 0) {
    alarm.minute = (ONE_HOUR-1);
  }
  else {
    alarm.minute--;
  }
}

// HOURS
void decrementAlarmHour(void) {
  if (alarm.hour == 0) {
    alarm.hour = time_format;
  }
  else {
    alarm.hour--;
  }
}
