#include "main.h"
#include "interrupts.h"

void update_second_isr(void* isr_context) {
  printf("INTERRUPT FIRED!\n");

  /* The TO (timeout) bit is set to 1 when the internal counter reaches zero. Once set by a
  timeout event, the TO bit stays set until explicitly cleared by a master peripheral. Write zero
  to the status register to clear the TO bit. */
  IOWR_ALTERA_AVALON_TIMER_STATUS(UPDATE_SECOND_BASE, 0);
}


int registerTimerInterrupt(void) {
  int isr_register_status;

  isr_register_status = alt_ic_isr_register(UPDATE_SECOND_IRQ_INTERRUPT_CONTROLLER_ID,
                                            UPDATE_SECOND_IRQ,
                                            update_second_isr,
                                            NULL,
                                            0x0);
  return isr_register_status;
}

void enableTimerInterrupt(void) {

 IOWR_ALTERA_AVALON_TIMER_CONTROL(UPDATE_SECOND_BASE,
                 ALTERA_AVALON_TIMER_CONTROL_CONT_MSK  
               | ALTERA_AVALON_TIMER_CONTROL_START_MSK
               | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}






/*
******PSEUDO-CODE*******

-------button ISR------:

switches = readSwitches();
button = readButtons();

switch(switches) {

  case CHANGE_ALARM :
    if (button == CHANGE_HOUR) {
      incrementAlarmHour();
    }
    else if (button == CHANGE_MINUTE) {
      incrementAlarmMinute();
    }
    break;

  case CHANGE_TIME :
    if (button == CHANGE_HOUR) {
      incrementTimeHour();
    }
    else if (button == CHANGE_MINUTE) {
      incrementTimeMinute();
    }
    break;

  case CHANGE_VOLUME :
    if (button == UP_BUTTON) {
      incrementVolume();
    }
    else if (button == DOWN_BUTTON) {
      decreaseVolume();
    }
    break;  

  // in this case, the user has multiple "modes" selected
  // indicate to user that this is the case (with flashing LED for ex.) or do nothing
  default :

}

*/
