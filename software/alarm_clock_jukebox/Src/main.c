#include "main.h"

/* the mode struct is global so that the callback functions 
in main.c can access it and determine the appropiate courses
of action */
struct mode mode;

int main(void) {

  // modde initialization: free running clock mode
  mode.invalid = FALSE;
  mode.display = DISP_CLOCK;
  mode.alarm = OFF;
  mode.config.on = FALSE;
  mode.config.hour = FALSE;
  mode.config.minute = FALSE;

  // module intialization
  alarmLEDoff();
  resetClockTime();
  resetAlarmTime();
  resetDisplay();

  // ISR registration
  if (timerSecondRegisterISR(&timerSecondISR) == ISR_REGISTRATION_SUCCESS) {
    //printf("timerSecondISR successively registered!\n");
    timerSecondEnableInterrupt();
  }
  else {
   //printf("ERROR: timerSecondISR unsuccessively registered!\n");
  }

  if (switchesRegisterISR(&switchesISR) == ISR_REGISTRATION_SUCCESS) {
    //printf("switchesISR successively registered!\n");
    switchesEnableInterrupt();
  }
  else {
   //printf("ERROR: switchesISR unsuccessively registered!\n");
  }

  if (buttonsRegisterISR(&buttonsISR) == ISR_REGISTRATION_SUCCESS) {
    //printf("buttonsISR successively registered!\n");
    buttonsEnableInterrupt();
  }
  else {
   //printf("ERROR: buttonsISR unsuccessively registered!\n");
  }

  if (timerPWMRegisterISR(&timerPWMISR) == ISR_REGISTRATION_SUCCESS) {
    //printf("timerPWMISR successively registered!\n");
  }
  else {
   //printf("ERROR: timerPWMISR unsuccessively registered!\n");
  }

  while(1) {}  
}


// -------------- ISR callbacks -------------------

/* ISR: update the time of the clock and depending on whether or not the user
is in config mode, carry the time digits. */
void timerSecondISR(void* isr_context) {

  // clear timeout bit because the internal counter for the timer reached zero
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_SECOND_BASE, 0);

  // temporary time struct for data transfer between modules and for //printf debugging
  struct time clock;
 
  if (mode.display == DISP_CLOCK) {
    if (mode.config.on == TRUE) {

      // digits should not carry over while configuring the time
      clock = upClockSecond(CARRY_OFF);

    }
    else if (mode.config.on == FALSE) {

      // since we're not in config mode, the time 
      // should normally count and carry.
      clock = upClockSecond(CARRY_ON);

      // check the alarm
      if (mode.alarm == ON) {

        struct time alarm;
        alarm = getAlarmTime();

        /* to avoid executing the following block of code everytime and to only call initializeSong() once, 
        we have to check whether or not the time is currently at XX:XX:00. 
        --> at 0 seconds, thats when the alarm will be activated */
        if ( (clock.second == 0) && (alarm.hour == clock.hour) && (alarm.minute == clock.minute) ) {

          // start the alarm!
          struct note_info note;
          note = initializeSong();

          //printf("BEEP! BEEP! BEEP! Alarm has gone off...\n");
          //printf("note.frequency == %d\n",note.frequency);
          //printf("note.duration == %d\n",note.duration);
          //printf("note.endofsong == %d\n",note.endofsong);

          writePWM(note.frequency);
          timerPWMEnableInterrupt(note.duration);

        }
      }

    }
    else {
      //printf("ERROR: mode.config.on has an invalid value\n");
    }

    // since we're currently in clock mode, 
    // we have to update the display after every second tick
    updateDisplay(clock);

  }
  else {
    // since the current time is not being displayed, 
    // we don't update the display
    clock = upClockSecond(CARRY_ON);
  }

  //printf("CLOCK TIME: %d:%d:%d\n",clock.hour,clock.minute,clock.second);

}


/* ISR determines user requested mode
Once determined, the system will update the display to match what was requested, 
and perform other actions such as turn on/off the alarm (for example)*/
void switchesISR(void* isr_context) {

  // reset edge capture register by writing to it 
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0);

  /* temporary mode struct for data transfer between modules and for testing
  the requested mode based on the switches state */
  struct mode mode_request;

  mode_request = determineMode();

  /* if an invalid mode is requested, nothing needs to change except for the mode struct.
  if a valid mode is requested, we have to determine what display to change to
  and/or if the alarm needs to be turned on/off */
  if (mode_request.invalid == FALSE) {

    /* don't need to update the display if we're currently displaying the 
    the same mode that was requested */
    if (mode_request.display != mode.display) {

      /* temporary display struct for data transfer between modules.
      *** although the struct's name is time, the information located 
      in this struct is not necessarily time data. This struct could contain
      volume or song information as well depending on the switch resolution. */
      struct time display;

      switch(mode_request.display) {
        case DISP_CLOCK: 
          display = getClockTime();
          break;

        case DISP_ALARM:
          display = getAlarmTime();
          break;

        case DISP_VOLUME:
          /* the current volume will be displayed on the "second" digits for the 7 seg display.
          For the moment this means that we're not going to check if the volume exceeds 99 */
          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          display.second = getVolume();
          break;

        case DISP_SONG:

          /* the current song will be displayed on the "second" digits for the 7 seg display.
          7 segment displays. For the moment this means that we're not going to check 
          if the song index exceeds 99  */
          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          display.second = getSongIndex();

          struct note_info note;
          note = initializeSong();

          //printf("switch to song display mode...\n");
          //printf("note.frequency == %d\n",note.frequency);
          //printf("note.duration == %d\n",note.duration);
          //printf("note.endofsong == %d\n",note.endofsong);

          writePWM(note.frequency);
          timerPWMEnableInterrupt(note.duration);

          break;

        default:
          printf("ERORR: An invalid display mode is requested\n");
      }

      // since the display mode was changed, we'll have to update the display
      updateDisplay(display);  
    }

    // occurs when mode_request.display == mode.display
    else { 
      //printf("The requested display mode is already active\n");
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
          //printf("song stopped because alarm is off and system is not currently in song display mode!\n");

        stopPWM();
        timerPWMDisableInterrupt();

      }
    }

    // occurs when mode_request.alarm == ON
    else {
      alarmLEDon();
    }
  }

  // occurs when mode_request.invalid == TRUE
  else {
    //printf("ERROR: An invalid mode was requested\n");
  }

  // make sure to update the mode struct before leaving ISR
  mode = mode_request;
  return;
}


/* ISR determines what sort of operation the user wants to perform for the
correctly active display mode (increase/decrease clock time, song select, etc.).
Once the requested operation is determined, the system will 
update the display to match what was requested */
void buttonsISR(void* isr_context) {

  /* if the user is not currently configuring something (time, alarm, etc), 
  then a button press won't do anything */
  if (mode.config.on == FALSE) {
    //printf("ERROR: Not currently in config mode! Button press ignored\n");

    /* don't forget to reset edge capture register by writing to it and before
    exiting ISR */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);

    return;
  }
  else {
    // determine the operation requested based on the button's state
    uint8_t buttons_state = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);

      /* temporary display struct for data transfer between modules.
      although the struct's name is time, the information located 
      in this struct is not necessarily time data. This struct could contain
      volume or song information as well. */
      struct time display;

      /* what happens next is entirely dependant on what the current display mode is, whether or not 
      the button press was an UP or DOWN operation, and finally if the config was for the 
      minute or hour time units. This scary case statement figures it out */
      switch(mode.display) {

        case DISP_CLOCK: 

          if (buttons_state == UP) {
            if (mode.config.hour == TRUE) {
              display = upClockHour();
            }
            else if (mode.config.minute == TRUE) {
              display = upClockMinute(CARRY_OFF);
            }
          }
          else if (buttons_state == DOWN) {
            if (mode.config.hour == TRUE) {
              display = downClockHour();
            }
            else if (mode.config.minute == TRUE) {
              display = downClockMinute(CARRY_OFF);
            }
          }
          break;

        case DISP_ALARM:

          if (buttons_state == UP) {
            if (mode.config.hour == TRUE) {
              display = upAlarmHour();
            }
            else if (mode.config.minute == TRUE) {
              display = upAlarmMinute();
            }
          }
          else if (buttons_state == DOWN) {
            if (mode.config.hour == TRUE) {
              display = downAlarmHour();
            }
            else if (mode.config.minute == TRUE) {
              display = downAlarmMinute();
            }
          }
          break;


        case DISP_VOLUME:

          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          if (buttons_state == UP) {
            display.second = upVolume();
          }
          else if (buttons_state == DOWN) {
            display.second = downVolume();
          }
          
          break;

        case DISP_SONG:

          /* immediately cut the PWM in case -> this should add an artificial 
          "pause" the time it takes to fetch and parse the song */
          stopPWM();

          display.hour = DONT_DISPLAY;
          display.minute = DONT_DISPLAY;
          if (buttons_state == UP) {
            display.second = upSong();
          }
          else if (buttons_state == DOWN) {
            display.second = downSong();
          }

          struct note_info note;
          note = initializeSong();

          //printf("button input while in display song mode...\n");
          //printf("note.frequency == %d\n",note.frequency);
          //printf("note.duration == %d\n",note.duration);
          //printf("note.endofsong == %d\n",note.endofsong);
          
          writePWM(note.frequency);
          timerPWMEnableInterrupt(note.duration);

          break;

        default:
          // if the switches.c module didn't mess up, this should never print!
          printf("ERORR: The system is currently in an invalid display mode!!\n");
      }

      // since the display mode was changed, we'll have to update the display
      updateDisplay(display);  
    }

  // we can't forget to reset edge capture register by writing to it!
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);

}


void timerPWMISR(void* isr_context) {

  //printf("timerPWMISR has fired!\n");

  /* The TO (timeout) bit is set to 1 when the internal counter reaches zero. Once set by a
  timeout event, the TO bit stays set until explicitly cleared by a master peripheral. 
  The TO bit is cleared by writing 0 to the status register. */
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_PWM_BASE, 0);

  struct note_info note;

  note = nextSongNote();
  //printf("note.frequency == %d\n",note.frequency);
  //printf("note.duration == %d\n",note.duration);
  //printf("note.endofsong == %d\n",note.endofsong);

  if (note.endofsong == FALSE) {
    writePWM(note.frequency);
    timerPWMEnableInterrupt(note.duration);
  }
  else if (note.endofsong == TRUE) {
    if (mode.display == DISP_SONG) {
      //printf("song played through once while in display song mode...\n");
      stopPWM();
      timerPWMDisableInterrupt();
    }
    else {
      //printf("Turn off alarm to stop the song!\n");
      note = initializeSong();
      //printf("note.frequency == %d\n",note.frequency);
      //printf("note.duration == %d\n",note.duration);
      //printf("note.endofsong == %d\n",note.endofsong);
      writePWM(note.frequency);
      timerPWMEnableInterrupt(note.duration);  
    }
  }

}






