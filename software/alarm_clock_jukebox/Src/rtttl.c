#include "rtttl.h"

uint8_t song_index = 0;

uint8_t getSong(void) {
  return song_index;
}

uint8_t upSong(void) {
  song_index++;
  return song_index;
}

uint8_t downSong(void) {
  song_index--;
  return song_index;
}

void playSong(void) {
  // not yet implemented
  return;
}

void stopSong(void) {
  // not yet implemented
  return;
}