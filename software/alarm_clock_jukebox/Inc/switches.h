#ifndef __SWITCHES_H
#define __SWITCHES_H

// C libraries
#include <stdint.h>
#include <stdbool.h>

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

// mode.invalid = {FALSE, TRUE}
// mode.config.on = {FALSE, TRUE}
// mode.config.hour = {FALSE, TRUE}
// mode.config.minute = {FALSE, TRUE}
#define FALSE 0 
#define TRUE 1

// mode.alarm = {OFF, ON}
#define OFF 0
#define ON 1

// mode.display = {DISP_CLOCK, DISP_ALARM, DISP_VOLUME, DISP_SONG}
#define DISP_CLOCK 0
#define DISP_ALARM 1
#define DISP_VOLUME 2
#define DISP_SONG 3

// error handling when an invalid mode is requested
#define VALID 0
#define INVALID 1

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

// each mode as determined by the switches (prefix SW to indicate SWITCHES)
#define SW_CLOCK              0b0000000000      
#define SW_CONFIG_CLOCK_MIN   0b0000000001
#define SW_CONFIG_CLOCK_HR    0b0000000010
#define SW_CONFIG_ALARM_MIN   0b0000000100
#define SW_CONFIG_ALARM_HR    0b0000001000
#define SW_CONFIG_SONG        0b0000010000
#define SW_CONFIG_VOLUME      0b0000100000
#define SW_ALARM              0b1000000000

#define NUM_VALID_MODES 8
#define NUM_MODE_STRUCT_MEMBERS 6

const uint16_t mode_lookup_table[NUM_VALID_MODES][NUM_MODE_STRUCT_MEMBERS] = {
  //  MODE                  DISPLAY        CONFIG.ON  CONFIG.HOUR  CONFIG.MINUTE  ALARM
  {   SW_CLOCK,             DISP_CLOCK,    FALSE,     FALSE,       FALSE,         OFF  },
  {   SW_CONFIG_CLOCK_MIN,  DISP_CLOCK,    TRUE,      FALSE,       TRUE,          OFF  },
  {   SW_CONFIG_CLOCK_HR,   DISP_CLOCK,    TRUE,      TRUE,        FALSE,         OFF  },
  {   SW_CONFIG_ALARM_MIN,  DISP_ALARM,    TRUE,      FALSE,       TRUE,          OFF  },
  {   SW_CONFIG_ALARM_HR,   DISP_ALARM,    TRUE,      TRUE,        FALSE,         OFF  },
  {   SW_CONFIG_SONG,       DISP_SONG,     TRUE,      FALSE,       FALSE,         OFF  },
  {   SW_CONFIG_VOLUME,     DISP_VOLUME,   TRUE,      FALSE,       FALSE,         OFF  },
  {   SW_ALARM,             DISP_CLOCK,    FALSE,     FALSE,       FALSE,         ON   },
};

// --------- invalid modes ----------
// these are not explicitly listed, but the actual determination of
// an invalid mode is done by testing the modulo 2 of the switch_state 
// if the associated value is not a multiple of 2, then the user has
// requested an invalid mode




#endif