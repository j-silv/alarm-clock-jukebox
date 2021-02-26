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

  // initialization
  mode.display = TIME_DISPLAY;
  mode.alarm = NOT_ARMED;
  mode.config.on = TRUE;
  mode.config.hour = FALSE;
  mode.config.minute = FALSE;
  alarmLEDoff();
  resetClockTime();
  resetAlarmTime();
  resetDisplay();

  /* the callback ISR is passed in for the registration. When the timer peripheral
  fires its interrupt, timerSecondISR() will be called
  timerSecondISR can be preceded with or without & (both pass in the function address); 
  because a function’s name can also be used to get function's address */
  if (timerSecondRegisterISR(&timerSecondISR) == ISR_REGISTRATION_SUCCESS) {
    printf("timerSecondISR successively registered!\n");
    timerSecondEnableInterrupt();
  }
  else {
   printf("ERROR: timerSecondISR unsuccessively registered!\n");
  }
  // if (timerPWMRegisterISR() == ISR_REGISTRATION_SUCCESS)... etc.



  while(1) {}  
}


// -------------- ISR callbacks -------------------

void timerSecondISR(void* isr_context) {

  /* The TO (timeout) bit is set to 1 when the internal counter reaches zero. Once set by a
  timeout event, the TO bit stays set until explicitly cleared by a master peripheral. 
  The TO bit is cleared by writing 0 to the status register. */
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_SECOND_BASE, 0);


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








