#ifndef library_h
#define library_h

#include "song.h"

typedef struct elmLibrary* addressLibrary;

struct elmLibrary {
    Song info;
    addressLibrary next;
    addressLibrary prev;
};

struct Library {
    addressLibrary head;
    addressLibrary tail;
};

void createLibrary(Library &L);
addressLibrary allocateLibrary(Song s);
void addSong(Library &L, Song s);
void showAllSongs(Library L);
Song* findSongById(Library L, int id);
void updateSong(Library &L, int id, Song newData);
void deleteSong(Library &L, int id, struct Playlist playlists[], int &playlistCount);
void searchSong(Library L);
Song* findSimilarSong(Library L, Song current);

#endif
