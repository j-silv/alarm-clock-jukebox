#ifndef __RTTTL_H
#define __RTTTL_H

// C libraries
#include <stdio.h>
#include <stdint.h>

#include "rtttl_songs.h"

struct note_info {
  char letter;
  int frequency;
  int duration;
  int endofsong;
};

#define FALSE 0
#define TRUE 1

#define ERROR_CHAR 'X'

uint8_t getSongIndex(void);
uint8_t upSong(void);
uint8_t downSong(void);
void initializeSong(void);
struct note_info nextSongNote(void);


#endif
