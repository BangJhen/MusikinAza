#ifndef playlist_h
#define playlist_h

#include "song.h"

typedef struct elmPlaylist* addressPlaylist;

struct elmPlaylist {
    Song info;
    addressPlaylist next;
};

struct Playlist {
    string nama;
    addressPlaylist head;
    addressPlaylist tail;
};

struct CurrentPlay {
    Song info;
    bool isPlaying;
    bool fromPlaylist;
    addressPlaylist currentPlaylistelm;
};

void createPlaylist(Playlist &P, string nama);
addressPlaylist allocatePlaylist(Song s);
void addToPlaylist(Playlist &P, Song s);
void removeFromPlaylist(Playlist &P, int id);
void showPlaylist(Playlist P);
void playFromPlaylist(Playlist P, CurrentPlay &cp, int id);
void updateSongInPlaylist(Playlist &P, int id, Song newData);
void deleteSongFromPlaylist(Playlist &P, int id);

#endif
