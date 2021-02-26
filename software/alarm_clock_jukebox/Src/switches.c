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
  if (checkInvalidMode(switches_state_request) == INVALID_MODE) {
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
  /* check edge case -> if the switches_state is equal to 1, then this is a valid state
  we have to check this, because, for example, 5 mod 2 = 1 mod 2 = 1, whereas
  the latter is a valid state, but the former is not!

  if the switch state is divisible by 2, then it is a valid state
  this means only one switch is currently active */
  if ( ((switches_state_request == 1) || (switches_state_request % 2) == 0) ) {
    return VALID_MODE;
  }

  else {
    return INVALID_MODE;
  }
}