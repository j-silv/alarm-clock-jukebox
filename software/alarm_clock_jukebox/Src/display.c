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
  uint8_t bcd[2];
  uint8_t ledseg[2];

  // HOURS
  bcd[1] = time.hour/10;
  bcd[0] = time.hour - bcd[1]*10;
  ledseg[1] = COM_ANODE_SEG_TABLE[(bcd[1])];
  ledseg[0] = COM_ANODE_SEG_TABLE[(bcd[0])];
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR1_BASE, ledseg[1]);
  IOWR_ALTERA_AVALON_PIO_DATA(HOUR0_BASE, ledseg[0]);

  // MINUTES
  bcd[1] = time.minute/10;
  bcd[0] = time.minute - bcd[1]*10;
  ledseg[1] = COM_ANODE_SEG_TABLE[(bcd[1])];
  ledseg[0] = COM_ANODE_SEG_TABLE[(bcd[0])];
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE1_BASE, ledseg[1]);
  IOWR_ALTERA_AVALON_PIO_DATA(MINUTE0_BASE, ledseg[0]);

  // SECONDS
  bcd[1] = time.second/10;
  bcd[0] = time.second - bcd[1]*10;
  ledseg[1] = COM_ANODE_SEG_TABLE[(bcd[1])];
  ledseg[0] = COM_ANODE_SEG_TABLE[(bcd[0])];
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND1_BASE, ledseg[1]);
  IOWR_ALTERA_AVALON_PIO_DATA(SECOND0_BASE, ledseg[0]);



}