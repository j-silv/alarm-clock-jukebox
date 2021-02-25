#include "display.h"

void resetDisplay(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR0_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(MIN1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(MIN0_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(SEC1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(SEC0_BASE, RESET_DISPLAY_VALUE);
}



/* Conversion decimal to BCD example (number 512):
dec = 512
bcd[2] = 512/100 = 5
bcd[1] = (512-5*100)/10 = 12/10 = 1
bcd[0] = (512 - (5*100 + 1*10))/1 = 2
*/

int convert3DigitDecimalToLED(int decimal) {
  int bcd[3] = {0x0,0x0,0x0};
  int ledseg_buffer = 0;
  
  // first convert the decimal to BCD
  bcd[2] = decimal/100;
  bcd[1] = (decimal - bcd[2]*100)/10;
  bcd[0] = decimal - (bcd[2]*100 + bcd[1]*10);

  // then convert BCD to LED segment data buffer
  // by passing in pointer to bcd array
  ledseg_buffer = convertBCDToLED(bcd);

  return ledseg_buffer;
}

int convertBCDToLED(int *bcd) {

  int i;
  int ledseg[3] = {0x0,0x0,0x0};
  int ledseg_buffer = 0x0;

  // shift by 8 bits each time through loop to target each digit
  // of the 7 seg display
  for (i=0; i < 3; i++) {
    // bcd[i] corresponds to a position of the SEG_TABLE and this position
    // is the associated BCD value
    ledseg[i] = COM_ANODE_SEG_TABLE[(bcd[i])];
    ledseg_buffer |= (ledseg[i] << 8*i);
  }
  return ledseg_buffer;
}

void updateHourTime(int hour) {
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, hour);
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR0_BASE, hour);
}

void updateMinutesTime(int minute) {
  IOWR_ALTERA_AVALON_PIO_DATA(MIN1_BASE, minute);
  IOWR_ALTERA_AVALON_PIO_DATA(MIN0_BASE, minute);
}

void updateSecondsTime(int second) {
  IOWR_ALTERA_AVALON_PIO_DATA(SEC1_BASE, second);
  IOWR_ALTERA_AVALON_PIO_DATA(SEC0_BASE, second);
}