/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include <unistd.h>
#include  "altera_avalon_pio_regs.h"

#define ADD 0x0
#define SUB 0x1
#define DIV 0x2
#define MULT 0x3

/*
COMMON CATHODE SEG MAPPING
dec binary hex
0	0111111	3F
1	0000110	06
2	1011011	5B
3	1001111	4F
4	1100110	66
5	1101101	6D
6	1111101	7D
7	0000111	07
8	1111111	7F
9	1001111	4F

COMMON ANODE SEG MAPPING
0	1000000	C0
1	1111001	F9
2	0100100	A4
3	0110000	B0
4	0011001	99
5	0010010	92
6	0000010	82
7	1111000	F8
8	0000000	80
9	0010000	90
*/

// array position [0] correspond a afficher 0, [1] -> 1, etc.
// position [10] -> tous les bits OFF
// position [11] -> le signe moins (-, segment G)
int SEG_TABLE[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF,0x3F};

// nous pouvons pas afficher plus que 999
#define MAX_ABS_VALUE 999


#endif /* __MAIN_H */
