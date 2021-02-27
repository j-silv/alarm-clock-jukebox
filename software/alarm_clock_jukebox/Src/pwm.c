#include "pwm.h"

uint8_t volume = 5;

uint8_t getVolume(void) {
  return volume;
}

uint8_t upVolume(void) {
  volume++;
  return volume;
}

uint8_t downVolume(void) {
  volume--;
  return volume;
}