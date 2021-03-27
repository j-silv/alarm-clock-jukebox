#include "rtttl.h"

uint8_t song_index = 0;

int notefreq[12] = {4186, 4434, 4698, 4978, 5274, 5587, 5919, 6271, 6644, 7040, 7458, 7902};
int defdur = 4;
int defscale = 6;
int bpm = 63;
int silence = 0;

/* p is a pointer to a const char -> we can change what to point at
but we can't change the actual value of the object that we're pointing at */
const char *p;

uint8_t getSongIndex(void) {
  return song_index;
}

uint8_t upSong(void) {
  /* song is an array of pointers of type const char. Since each pointer has the same
  size in memory (char* takes up 1 byte) if we divide the size of the entire array by the size
  of 1 char pointer, we'll get the number char pointers and thus the number of songs */
  if (song_index == sizeof(song)/sizeof(song[0])){

    // wrap around when scrolling through songs
    song_index = 0;
  }
  else {
    song_index++;
  }
  return song_index;
}

uint8_t downSong(void) {
  if (song_index == 0) {

    // wrap around when scrolling through songs
    song_index = sizeof(song)/sizeof(song[0]);
  }
  else {
    song_index--;
  }
  return song_index;
}

int note2freq(int note) {
  return notefreq[note % 12] / (1 << (9 - (note / 12)));
}

void initializeSong(void) {

  p = song[song_index];
  
  // Skip name
  while (*p && *p != ':') p++;
  if (!*p) {printf("ERROR in rtttl.c: 0 after name:\n"); return;}
  p++;

  // Parse defaults
  while (*p) {
    char param;
    int value;

    while (*p == ' ') p++;
    if (!*p) {printf("ERROR in rtttl.c: defaults: never found\n"); return;}
    if (*p == ':') break;

    param = *p++;
    if (*p != '=') {printf("ERROR in rtttl.c: = never found\n"); return;}
    
    p++;
    value = 0;
    while (*p >= '0' && *p <= '9') value = value * 10 + (*p++ - '0');

    switch (param) {
      case 'd': defdur = 32 / value; break;
      case 'o': defscale = value; break;
      case 'b': bpm = value; break;
    }

    while (*p == ' ') p++;
    if (*p == ',') p++;
  }
  p++;

}

// used to get the first note of the song and the subsequent ones
struct note_info nextSongNote(void) {

  int note = -1;
  int scale = defscale;
  int dur = defdur;
  int ms;
  int freq;
  struct note_info payload;

  if (!*p) {printf("End of song!\n");payload.endofsong = TRUE; return payload;}

  else {

    // Skip whitespace
    while (*p == ' ') p++;
    if (!*p) {printf("ERROR in rtttl.c: 0 found during nextSongNote\n");payload.letter = ERROR_CHAR; return payload;}

    // Parse duration
    if (*p >= '0' && *p <= '9') {
      int value = 0;
      while (*p >= '0' && *p <= '9') value = value * 10 + (*p++ - '0');

      dur = 32 / value;
    }

    // Parse note
    switch (*p) {
      case 0: printf("End of song!\n"); payload.endofsong = TRUE; return payload; // i *think* means the null-terminated character is reached
      case 'C': case 'c': note = 0; break;
      case 'D': case 'd': note = 2; break;
      case 'E': case 'e': note = 4; break;
      case 'F': case 'f': note = 5; break;
      case 'G': case 'g': note = 7; break;
      case 'A': case 'a': note = 9; break;
      case 'H': case 'h': note = 11; break;
      case 'B': case 'b': note = 11; break;
      case 'P': case 'p': note = -1; break;
    }

    // this info is picked up for the LED piano module
    payload.letter = note;

    p++;
    if (*p == '#') {
      note++;
      p++;
    }
    if (*p == 'b') {
      note--;
      p++;
    }

    // Parse special duration
    if (*p == '.') {
      dur += dur / 2;
      p++;
    }

    // Parse scale
    if (*p >= '0' && *p <= '9') scale = (*p++ - '0');

    // Parse special duration (again...)
    if (*p == '.') {
      dur += dur / 2;
      p++;
    }

    // Skip delimiter
    while (*p == ' ') p++;
    if (*p == ',') p++;

    // Play note
    ms = dur * 60000 / (bpm * 8);
    if (note == -1) {
      freq = 0;
    } else {
      freq = note2freq((scale + 1) * 12 + note);
    }


    payload.frequency = freq;
    payload.duration = ms;
    payload.endofsong = FALSE;
    
    return payload;   
    
  }
}