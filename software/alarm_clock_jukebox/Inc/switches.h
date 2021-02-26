#ifndef __SWITCHES_H
#define __SWITCHES_H

// C libraries
#include <stdint.h>

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"

struct config {
  uint8_t on;
  uint8_t hour;
  uint8_t minute;
};
struct mode{
  uint8_t invalid;
  uint8_t display;
  uint8_t alarm;
  struct config config;
};

// values possible for the mode struct members
#define FALSE 0
#define TRUE 1
#define NOT_ARMED 2
#define ARMED 3
#define CLOCK_DISPLAY 4
#define ALARM_DISPLAY 5
#define VOLUME_DISPLAY 6
#define SONG_DISPLAY 7

// error handling when an invalid mode is requested
#define INVALID_MODE 8
#define VALID_MODE 9

struct mode determineMode(void);
uint8_t checkInvalidMode(uint16_t switches_state_request);

//      |SWITCHES|
// | = = = = = = = = = = = |
// | 9 8 7 6 5 4 3 4 2 1 0 |
// 
// SWITCH 9: N/A
// SWITCH 8: N/A
// SWITCH 7: N/A
// SWITCH 6: switch ON - > config volume
// SWITCH 5: switch ON - > config song
// SWITCH 4: switch ON - > config alarm hour
// SWITCH 3: switch ON - > config alarm minute
// SWITCH 2: switch ON - > config clock hour
// SWITCH 1: switch ON - > config clock minute
// SWITCH 0: switch ON - > alarm on

// each mode as determined by the switches
#define CLOCK              0b0000000000      
#define CONFIG_CLOCK_MIN   0b0000000001
#define CONFIG_CLOCK_HR    0b0000000010
#define CONFIG_ALARM_MIN   0b0000000100
#define CONFIG_ALARM_HR    0b0000001000
#define CONFIG_SONG        0b0000010000
#define CONFIG_VOLUME      0b0000100000
#define ALARM              0b1000000000

// --------- valid modes ----------

#define NUM_VALID_MODES 8
#define NUM_MODE_STRUCT_MEMBERS 6

const uint16_t mode_lookup_table[NUM_VALID_MODES][NUM_MODE_STRUCT_MEMBERS] = {
  //  MODE               DISPLAY         CONFIG.ON  CONFIG.HOUR  CONFIG.MINUTE  ALARM
  {   CLOCK,             CLOCK_DISPLAY,  FALSE,     FALSE,       FALSE,         NOT_ARMED  },
  {   CONFIG_CLOCK_MIN,  CLOCK_DISPLAY,  TRUE,      FALSE,       TRUE,          NOT_ARMED  },
  {   CONFIG_CLOCK_HR,   CLOCK_DISPLAY,  TRUE,      TRUE,        FALSE,         NOT_ARMED  },
  {   CONFIG_ALARM_MIN,  ALARM_DISPLAY,  TRUE,      FALSE,       TRUE,          NOT_ARMED  },
  {   CONFIG_ALARM_HR,   ALARM_DISPLAY,  TRUE,      TRUE,        FALSE,         NOT_ARMED  },
  {   CONFIG_SONG,       SONG_DISPLAY,   TRUE,      FALSE,       FALSE,         NOT_ARMED  },
  {   CONFIG_VOLUME,     VOLUME_DISPLAY, TRUE,      FALSE,       FALSE,         NOT_ARMED  },
  {   ALARM,             CLOCK_DISPLAY,  FALSE,     FALSE,       FALSE,         ARMED      },
};

// --------- invalid modes ----------
// these are not explicitly listed, but the actual determination of
// an invalid mode is done by testing the modulo 2 of the switch_state 
// if the associated value is not a multiple of 2, then the user has
// requested an invalid mode




#endif