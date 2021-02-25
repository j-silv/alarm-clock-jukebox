/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DISPLAY_H
#define __DISPLAY_H

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

// C libraries
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"

// array position [0] corresponds to displaying 0, [1] -> 1, etc.
// position [10] -> all segments are OFF
// position [11] -> the minus sign (-, segment G)
uint8_t COM_ANODE_SEG_TABLE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x3F};

// 999 is the maximum value we can display with 3 LED segment displays
#define MAX_ABS_VALUE 999

#define RESET_DISPLAY_VALUE 0xC0

void resetDisplay(void);

int convert3DigitDecimalToLED(int decimal);
int convertBCDToLED(int *bcd);
void updateHourTime(int hour);
void updateMinutesTime(int minute);
void updateSecondsTime(int second);

#endif
