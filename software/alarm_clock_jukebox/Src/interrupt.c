#include "interrupt.h"

// -------------- API -----------------------
// these are the functions that main.c calls
int registerISR(void) {
  if (registerTimerSecondISR() != ISR_REGISTRATION_SUCCESS) {
    return ISR_REGISTRATION_FAILURE;
  }
  else {
    return ISR_REGISTRATION_SUCCESS;
  }
}

void enableTimerSecondISR(void) {
 IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_SECOND_BASE,
                 ALTERA_AVALON_TIMER_CONTROL_CONT_MSK  
               | ALTERA_AVALON_TIMER_CONTROL_START_MSK
               | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}


// -------------- ISRs -----------------------
// these are the callback functions that are called once the associated interrupt has fired

void timerSecondISR(void* isr_context) {
  /* The TO (timeout) bit is set to 1 when the internal counter reaches zero. Once set by a
  timeout event, the TO bit stays set until explicitly cleared by a master peripheral. 
  The TO bit is cleared by writing 0 to the status register. */
  IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_SECOND_BASE, 0);

  timerSecondCallback();
}


// -------------- ISR registration functions ---------------- 
uint8_t registerTimerSecondISR(void) {
  uint8_t isr_register_status;

  isr_register_status = alt_ic_isr_register(TIMER_SECOND_IRQ_INTERRUPT_CONTROLLER_ID,
                                            TIMER_SECOND_IRQ,
                                            timerSecondISR,
                                            NULL,
                                            0x0);
  return isr_register_status;
}