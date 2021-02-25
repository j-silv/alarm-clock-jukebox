#include "led.h"

void alarmLEDoff(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, LED_OFF);
}

void alarmLEDon(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, LED_ON);
}

void alarmLEDtoggle(void) {
  int led_state;
  led_state = IORD_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE);
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, !led_state);
}