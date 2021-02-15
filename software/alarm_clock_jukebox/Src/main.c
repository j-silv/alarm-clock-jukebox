#include "main.h"
#include "interrupts.h"

int main(void) {


  if (registerTimerInterrupt() == ISR_REGISTER_SUCCESS) {
    printf("ISR registered!\n");

    // enable the appropiate update_second peripheral
    enableTimerInterrupt();
  }
  else {
    printf("ERROR: ISR unsuccessfully registered!\n");
  }


  while(1) {
  }  
}








