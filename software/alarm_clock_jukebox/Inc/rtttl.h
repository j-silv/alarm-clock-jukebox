#ifndef __RTTTL_H
#define __RTTTL_H

// C libraries
#include <stdio.h>
#include <stdint.h>

#include "rtttl_songs.h"

struct note_info {
  int frequency;
  int duration;
  int endofsong;
};

#define FALSE 0
#define TRUE 1

uint8_t getSong(void);
uint8_t upSong(void);
uint8_t downSong(void);
struct note_info playSong(void);
struct note_info getNote(void);


#endif
