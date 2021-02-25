#include "main.h"

int main(void) {
  if (registerISR() == ISR_REGISTRATION_FAILURE) {
    printf("ERROR: Interrupts unsuccessfully initialized!\n");
  }
  else {
    printf("Interrupts successively initialized!\n");
    enableTimerSecondISR();
  }


  while(1) {
  }  
}


// -------------- ISR callbacks -------------------
// these are the main.c callback functions that the ISRs call from interrupt.c

void timerSecondCallback(void) {
  printf("timerSecond interrupt has fired!\n");
}








