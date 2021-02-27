/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

// C libraries
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"

/*
COMMON CATHODE SEG MAPPING:    
dec   binary    hex
0	    0111111	  3F
1	    0000110	  06
2	    1011011	  5B
3	    1001111  	4F
4	    1100110  	66
5	    1101101  	6D
6	    1111101	  7D
7	    0000111	  07
8	    1111111	  7F
9	    1001111	  4F

COMMON ANODE SEG MAPPING:
dec   binary    hex
0	    1000000	  C0
1	    1111001	  F9
2	    0100100	  A4
3	    0110000	  B0
4	    0011001	  99
5	    0010010	  92
6	    0000010	  82
7	    1111000	  F8
8	    0000000	  80
9	    0010000	  90
*/

// array position [0] corresponds to displaying 0, [1] -> 1, etc.
// position [10] -> all segments are OFF. If a member of the time
// struct has a BCD value of 10, then after BCD to LED conversion, the resulting digits for that time unit
// will be off. Thus after referencing the COM_ANODE_SEG_TABLE, those time unit digits will be OFF
const uint8_t COM_ANODE_SEG_TABLE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};

#define RESET_DISPLAY_VALUE 0xC0

// 999 is the maximum value we can display with 3 LED segment displays
#define MAX_ABS_VALUE 999
// how many digits are displayed on the 7 seg display
#define NUM_DISPLAY_DIGITS 6
// how many different time units are there (seconds, minutes, hours)
#define NUM_TIME_UNITS 3
// what is the precision of each time unit (how many digits for each time unit)
#define NUM_DIGITS_FOR_UNIT 2

/* this is a macro for the time struct, which will explicitly let the display module know to
not display the digits for a particular time unit (for example, in alarm config mode, we don't
want to show the seconds time unit). */
#define DONT_DISPLAY 100

/* if the DONT_DISPLAY macro was detected within one of the time struct members, this macro gives the index
of the COM_ANODE_SEG_TABLE where the LED segments will be turned off. */
#define DIGITS_OFF 10

struct time{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
};

void resetDisplay(void);
void updateDisplay(struct time time);

#endif
