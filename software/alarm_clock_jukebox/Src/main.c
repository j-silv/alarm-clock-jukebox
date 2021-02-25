#include "main.h"

int main(void) {

  typedef struct {
    volatile uint8_t on;
    volatile uint8_t hour;
    volatile uint8_t minute;
  } config_struct;

  typedef struct {
    volatile uint8_t display;
    volatile uint8_t alarm;
    config_struct config;
  } mode_struct;

  mode_struct mode;
  mode.display = TIME_DISPLAY;
  mode.alarm = NOT_ARMED;
  mode.config.on = FALSE;
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
  printf("timerSecond interrupt has fired!\n");
  alarmLEDtoggle();
}








