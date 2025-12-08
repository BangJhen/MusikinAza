#ifndef player_h
#define player_h

#include "library.h"
#include "playlist.h"

void playSong(Library L, CurrentPlay &cp, int id);
void stopSong(CurrentPlay &cp);
void nextSong(Library L, CurrentPlay &cp);
void prevSong(Library L, CurrentPlay &cp);

#endif
