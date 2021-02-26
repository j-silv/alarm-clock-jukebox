#include "display.h"

void resetDisplay(void) {
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR0_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE0_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND1_BASE, RESET_DISPLAY_VALUE);
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND0_BASE, RESET_DISPLAY_VALUE);
}

/* Conversion decimal to BCD example (number 512):
dec = 512
bcd[2] = 512/100 = 5
bcd[1] = (512-5*100)/10 = 12/10 = 1
bcd[0] = (512 - (5*100 + 1*10))/1 = 2
*/
// for the moment, this is hard coded without any for loops
void updateDisplay(struct time time) {
  uint8_t bcd[6];
  uint8_t ledseg[6];

  // determine BCD values for hours, minutes, seconds
  bcd[5] = time.hour/10;
  bcd[4] = time.hour - bcd[5]*10;
  bcd[3] = time.minute/10;
  bcd[2] = time.minute - bcd[3]*10;
  bcd[1] = time.second/10;
  bcd[0] = time.second - bcd[1]*10;

  // convert BCD values to LED segment values
  ledseg[5] = COM_ANODE_SEG_TABLE[(bcd[5])];
  ledseg[4] = COM_ANODE_SEG_TABLE[(bcd[4])];
  ledseg[3] = COM_ANODE_SEG_TABLE[(bcd[3])];
  ledseg[2] = COM_ANODE_SEG_TABLE[(bcd[2])];
  ledseg[1] = COM_ANODE_SEG_TABLE[(bcd[1])];
  ledseg[0] = COM_ANODE_SEG_TABLE[(bcd[0])];

  // write to display port
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, ledseg[5]);
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR0_BASE, ledseg[4]);
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE1_BASE, ledseg[3]);
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE0_BASE, ledseg[2]);
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND1_BASE, ledseg[1]);
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND0_BASE, ledseg[0]);
}