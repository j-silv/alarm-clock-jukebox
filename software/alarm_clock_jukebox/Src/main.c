#include "main.h"

/* the mode struct is global so that the callback functions 
in main.c can access it and determine the appropiate courses
of action */
struct mode mode;

int main(void) {

  // initialization to "CLOCK" mode
  mode.invalid = FALSE;
  mode.display = DISP_CLOCK;
  mode.alarm = OFF;
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


/* This is the main ISR that is called whenever the second timer fires its interrupt. 
This ISR lets us update the time of the clock and depending on whether or not the user
is in config mode, carry the time digits. */
void timerSecondISR(void* isr_context) {

  /* The TO (timeout) bit is set to 1 when the internal counter reaches zero. Once set by a
  timeout event, the TO bit stays set until explicitly cleared by a master peripheral. 
  The TO bit is cleared by writing 0 to the status register. */
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_SECOND_BASE, 0);

  // temporary time struct for data transfer between modules and printf debugging
  struct time clock;
 
  if (mode.display == DISP_CLOCK) {
    if (mode.config.on == TRUE) {
      // since we're in config, we don't want to carry the digits
      clock = upClockSecond(CARRY_OFF);
    }
    else if (mode.config.on == FALSE) {

      // since we're not in config, the time should normally count and carry
      clock = upClockSecond(CARRY_ON);
    }
    else {
      printf("ERROR: mode.config.on is invalid\n");
    }

    // since the time is being displayed, we'll have to update the display
    updateDisplay(clock);


  }
  else {
    // since the current time is not being displayed, we don't update the display
    clock = upClockSecond(CARRY_ON);
  }

  // for debugging purposes:
  printf("The clock time is currently: %d:%d:%d\n",clock.hour,clock.minute,clock.second);
}



/* This ISR lets us determine what mode the user is currently requesting.
Once this mode is determined, the system will update the display to match what was requested,
and perform other actions such as turn on/off the alarm and on/off a song*/
void switchesISR(void* isr_context) {

  // reset edge capture register by writing to it 
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0);

  /* temporary mode struct for data transfer between modules and for testing
  the requested mode based on the switches state */
  struct mode mode_request;

  mode_request = determineMode();

  /*// debugging purposes
  printf("mode_request.invalid == %d\n", mode_request.invalid);
  printf("mode_request.display == %d\n", mode_request.display);
  printf("mode_request.config.on == %d\n", mode_request.config.on);
  printf("mode_request.config.hour == %d\n", mode_request.config.hour);
  printf("mode_request.config.minute == %d\n", mode_request.config.minute);
  printf("mode_request.alarm == %d\n", mode_request.alarm);*/


  /* if an invalid mode is requested, nothing needs to change except for the mode struct
  if however a valid mode is requested, we have to determine what display to change to
  and/or if the alarm needs to be turned on/off */
  if (mode_request.invalid == FALSE) {

    /* if we're already displaying the same mode that was requested, we don't need 
    need to update the display. Thus we can skip the following if statement*/
    if (mode_request.display != mode.display) {

      /* temporary display struct for data transfer between modules.
      although the struct's name is time, the information located 
      in this struct is not necessarily time data. This struct could contain
      volume or song information as well. */
      struct time display;

      switch(mode_request.display) {
        case DISP_CLOCK: 
          display = getClockTime();
          break;

        case DISP_ALARM:
          display = getAlarmTime();
          break;

        case DISP_VOLUME:
          /* the current volume will be displayed on the "second" 
          7 segment displays. For the moment this means that we're not going
          to check if the volume exceeds 99 (max number that can be displayed with 2 digits) */
          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          display.second = getVolume();
          break;

        case DISP_SONG:
          /* the current song will be displayed on the "second" 
          7 segment displays. For the moment this means that we're not going
          to check if the song index exceeds 99 (max number that can be displayed with 2 digits) */
          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          display.second = getSong();
          // call playSong() here
          break;

        default:
          printf("ERORR: An invalid display mode is requested\n");
      }

      // since the display mode was changed, we'll have to update the display
      updateDisplay(display);  
    }

    // (mode_request.display == mode.display)
    else { 
      printf("The requested display mode is already active\n");
    }

    // update the alarm mode if necessary
    if (mode_request.alarm == OFF) {
      alarmLEDoff();
      
      /* only stop the song if we're not in the song selection display.
      otherwise, the song that is being sampled while on this display will suddenly
      stop playing. A song should only stop playing if an armed alarm went off,
      and then a user decides to turn off said alarm, OR if a user changes from
      the song display menu to any other menu */
      if (mode_request.display != DISP_SONG) {
        //stopSong();
      }
    }

    // (mode_request.alarm == ON)
    else {
      alarmLEDon();
    }
  }

  // (mode_request.invalid == TRUE)
  else {
    printf("ERROR: An invalid mode was requested\n");
  }

  // make sure to update the mode struct before leaving ISR
  mode = mode_request;
  return;

}








