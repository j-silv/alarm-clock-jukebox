#include "main.h"

/* the mode struct is global so that the callback functions 
in main.c can access it and determine the appropiate courses
of action */
struct mode mode;

int main(void) {

  // initialization
  mode.invalid = FALSE;
  mode.display = CLOCK_DISPLAY;
  mode.alarm = NOT_ARMED;
  mode.config.on = FALSE;
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

  if (switchesRegisterISR(&switchesISR) == ISR_REGISTRATION_SUCCESS) {
    printf("switchesISR successively registered!\n");
    switchesEnableInterrupt();
  }
  else {
   printf("ERROR: switchesISR unsuccessively registered!\n");
  }





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

 
  if (mode.display == CLOCK_DISPLAY) {
    // temporary time struct for data transfer between modules
    struct time clock;

    if (mode.config.on == TRUE) {

      // since we're in config, we don't want to carry the digits
      clock = upClockSecond(CARRY_OFF);
      printf("The clock time is currently: %d:%d:%d\n",clock.hour,clock.minute,clock.second);
    }
    else if (mode.config.on == FALSE) {

      // since we're not in config, the time should normally count and carry
      clock = upClockSecond(CARRY_ON);
      printf("The clock time is currently: %d:%d:%d\n",clock.hour,clock.minute,clock.second);
    }
    else {
      printf("ERROR: mode.config.on is invalid\n");
    }

    // since the time is being displayed, we'll have to update the display
    updateDisplay(clock);


  }
  else {
    // since the current time is not being displayed, we don't update the display
    upClockSecond(CARRY_ON);
  }
}


void switchesISR(void* isr_context) {

  // for debugging purposes -> acknowledgement that interrupt has succesively fired
  printf("switches interrupt has fired!\n");

  // reset edge capture register by writing to it 
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0);

  /* temporary mode struct for data transfer between modules and for testing
  the requested mode based on the switches state */
  struct mode mode_request;

  mode_request = determineMode();

  printf("mode_request.invalid == %d\n", mode_request.invalid);
  printf("mode_request.display == %d\n", mode_request.display);
  printf("mode_request.config.on == %d\n", mode_request.config.on);
  printf("mode_request.config.hour == %d\n", mode_request.config.hour);
  printf("mode_request.config.minute == %d\n", mode_request.config.minute);
  printf("mode_request.alarm == %d\n", mode_request.alarm);

  /* Read the PIO to delay ISR exit. This is done to prevent a
  spurious interrupt in systems with high processor -> pio
  latency and fast interrupts. */
  IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE); 
}








