#include "led.h"

void alarmLEDoff(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, LED_OFF);
}

void alarmLEDon(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, LED_ON);
}

void alarmLEDtoggle(void) {
  volatile uint8_t led_state;
  led_state = IORD_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE);
  IOWR_ALTERA_AVALON_PIO_DATA(LED_ALARM_BASE, !led_state);
}

void writeLEDPiano(char note) {
  uint8_t led_piano_keys;

  switch(note) {
    case 0: led_piano_keys = 0b0000000; break;
    case 'G': case 'g': led_piano_keys = 0b1000000; break;
    case 'A': case 'a': led_piano_keys = 0b0100000; break;
    case 'B': case 'b': led_piano_keys = 0b0010000; break;
    case 'C': case 'c': led_piano_keys = 0b0001000; break;
    case 'D': case 'd': led_piano_keys = 0b0000100; break;
    case 'E': case 'e': led_piano_keys = 0b0000010; break;
    case 'F': case 'f': led_piano_keys = 0b0000001; break;
    case 'P': case 'p': led_piano_keys = 0b0000000; break;
    default: led_piano_keys = 0b0000000; break;
  }

  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIANO_BASE, led_piano_keys);
}

void LEDPianoOff(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIANO_BASE, 0b0000000);
}