#include "interrupt.h"

/* this registration functions receives a pointer to an ISR function which takes
in a pointer to a data structure (isr_context) as a parameter, and does not
return any value (void). ISRFunction() will be called once the timerSecond
interrupt fires, and this ISR resides in main.c */
uint8_t timerSecondRegisterISR(void (*timerSecondISR)(void *isr_context)) {
  uint8_t isr_register_status;

  isr_register_status = alt_ic_isr_register(TIMER_SECOND_IRQ_INTERRUPT_CONTROLLER_ID,
                                            TIMER_SECOND_IRQ,
                                            timerSecondISR,
                                            NULL,
                                            0x0);
  return isr_register_status;
}

void timerSecondEnableInterrupt(void) {
 IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_SECOND_BASE,
                 ALTERA_AVALON_TIMER_CONTROL_CONT_MSK  
               | ALTERA_AVALON_TIMER_CONTROL_START_MSK
               | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}

uint8_t switchesRegisterISR(void (*switchesISR)(void *isr_context)) {
  uint8_t isr_register_status;

  isr_register_status = alt_ic_isr_register(SWITCHES_IRQ_INTERRUPT_CONTROLLER_ID,
                                            SWITCHES_IRQ,
                                            switchesISR,
                                            NULL,
                                            0x0);
  return isr_register_status;
}


uint8_t buttonsRegisterISR(void (*buttonsISR)(void *isr_context)) {
  uint8_t isr_register_status;

  isr_register_status = alt_ic_isr_register(BUTTONS_IRQ_INTERRUPT_CONTROLLER_ID,
                                            BUTTONS_IRQ,
                                            buttonsISR,
                                            NULL,
                                            0x0);
  return isr_register_status;
}


void switchesEnableInterrupt(void) {
  // enable all switches to fire interupts
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCHES_BASE, SWITCHES_INTERRUPT_MASK);
  
  // reset the edge capture register
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCHES_BASE, 0);
}

void buttonsEnableInterrupt(void) {
  // enable all buttons to fire interupts
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTONS_BASE, BUTTONS_INTERRUPT_MASK);
  
  // reset the edge capture register
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 0);
}


uint8_t timerPWMRegisterISR(void (*timerPWMISR)(void *isr_context)) {
  uint8_t isr_register_status;

  isr_register_status = alt_ic_isr_register(TIMER_PWM_IRQ_INTERRUPT_CONTROLLER_ID,
                                            TIMER_PWM_IRQ,
                                            timerPWMISR,
                                            NULL,
                                            0x0);
  return isr_register_status;
}

void timerPWMEnableInterrupt(int timeout) {
  // timeout is in miliseconds -> convert to seconds
  // set period based on input timeout variable; writing to the period 
  // registers stops the counter which automatically loads reigster value
  uint32_t period = (NIOS_CLOCK_FREQ/1000)*timeout;

  //write to high and low registers
  IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_PWM_BASE, period);
  // shift by 16 to take into account high bits
  IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_PWM_BASE, (period >> AVALON_TIMER_PERIOD_WIDTH));

  // start timer and enable interrupt
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_PWM_BASE, 
                 ALTERA_AVALON_TIMER_CONTROL_START_MSK
               | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);
}

void timerPWMDisableInterrupt(void) {
  // set ITO to 0 (thus disabling interrupts)
  IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_PWM_BASE, 0);
}
