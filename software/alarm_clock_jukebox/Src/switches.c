#include "switches.h" 

struct mode determineMode(void) {

  /* if a valid mode is requested, this struct is changed and passed to main.c
  if an invalid mode was requested, then the old mode struct which was determined based off
  a valid mode request is resent to main.c 
  static variable so that everytime this function is called from the switches 
  ISR, the current mode is known allowing us to determine if an 
  invalid mode was requested */
  static struct mode mode;

  // this variable lets us test whether or not an invalid mode was requested
  volatile uint16_t switches_state_request = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);

  // check if the request is invalid
  if (checkInvalidMode(switches_state_request) == INVALID) {
    mode.invalid = TRUE;
    return mode;
  }

  else {
    // now that we know the mode request is valid, let's determine what it is
    mode.invalid = FALSE;

    uint8_t i = 0;

    // check for the valid mode request in lookup table
    while (switches_state_request != mode_lookup_table[i][0]) {
      i++;
      // catch error in case the bounds of the lookup table are exceeded
      if (i == NUM_VALID_MODES) {
        break;
      }
    }

    // once the valid mode request is find, the while loop ends and we have found
    // the correct mode; its location is determined by the index i
    // at this point, we can update the members of the mode struct
    mode.display = mode_lookup_table[i][1];
    mode.config.on = mode_lookup_table[i][2];
    mode.config.hour = mode_lookup_table[i][3];
    mode.config.minute = mode_lookup_table[i][4];
    mode.alarm = mode_lookup_table[i][5];

    return mode;
  }

}

uint8_t checkInvalidMode(uint16_t switches_state_request) {
  // check if an unused switch was turned on
  uint8_t i = 0;

  do {
    // if the entire array of unused_switches was searched but an
    // unused switch was not activated, then exit while loop
    if (i == NUM_UNUSED_SWITCHES) {
      break;
    }
    // if an unused switch was activated, exit function and indicate that
    // an invalid mode was selected
    else if (switches_state_request == unused_switches[i]) {
      return INVALID;
    }

    // increment index of unused_switches array
    i++;

  } while(1);

  // now that we know an unused switch is not activated, we need to verify that 
  // the used switches are in a valid configuration
  if ( isPowerOfTwoOrZero(switches_state_request) == TRUE ) {
    return VALID;
  }

  else {
    return INVALID;
  }
}


/***** Determining whether or not a single switch is active (valid mode) ****

if the switch state is a power of 2 or 0, then
it is a valid mode. Otherwise more than one switch is activated, which 
means that the mode requested is invalid....
---------------------------------------------
example with 3 bits: 000

valid modes (power of 2 or 0)       : 0, 1, 2, 4
invalid modes (not power of 2 or 0) : 3, 5, 6, 7

0 & -1  = 0 -> valid!
1 & 0   = 0 -> valid!
2 & 1   = 0 -> valid!
4 & 3   = 0 -> valid!

3 & 2  != 0 -> invalid!
5 & 4  != 0 -> invalid!
6 & 5  != 0 -> invalid!
7 & 6  != 0 -> invalid!
---------------------------------------------
*/ 

uint8_t isPowerOfTwoOrZero(uint16_t value) {
  if ((value & (value-1)) == 0) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}