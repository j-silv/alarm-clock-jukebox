#include "main.h"

/* the mode struct is global so that the callback functions 
in main.c can access it and determine the appropiate courses
of action */
struct config {
  uint8_t on;
  uint8_t hour;
  uint8_t minute;
};

struct mode{
  uint8_t display;
  uint8_t alarm;
  struct config config;
};

struct mode mode;

int main(void) {

  mode.display = TIME_DISPLAY;
  mode.alarm = NOT_ARMED;
  mode.config.on = TRUE;
  mode.config.hour = FALSE;
  mode.config.minute = FALSE;

  alarmLEDoff();
  resetClockTime();
  resetAlarmTime();
  resetDisplay();

  if (registerISR() == ISR_REGISTRATION_FAILURE) {
    printf("ERROR: Interrupts unsuccessfully initialized!\n");
  }
  else {
    printf("Interrupts successively initialized!\n");
    enableTimerSecondISR();
  }

  while(1) {}  
}


// -------------- ISR callbacks -------------------
// these are the main.c callback functions that the ISRs call from interrupt.c

void timerSecondCallback(void) {
  // for debugging purposes -> acknowledgement that interrupt has succesively fired
  //printf("timerSecond interrupt has fired!\n");
  alarmLEDtoggle();

 

  /* if we're currently configuring the current time, the display
  should not overflow its digits (for ex., at sec = 60, the minute should not
  pass to 1 */
  if (mode.display == TIME_DISPLAY) {
    if (mode.config.on == TRUE) {

      // temporary time struct for data transfer between modules
      struct time clock;

      clock = updateTime(CLOCK,SECOND,UP,CARRY_OFF);
      printf("The clock time is currently: %d:%d:%d\n",clock.hour,clock.minute,clock.second);
    }
  }



  //payload = convertBCD2LED(clock_time);
  //updateDisplay(payload);
}








