#ifndef musikinAza_h
#define musikinAza_h

#include <iostream>
#include <string>
using namespace std;

typedef struct NodeLibrary* addressLibrary;
typedef struct NodePlaylist* addressPlaylist;

struct Song {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

struct NodeLibrary {
    Song info;
    addressLibrary next;
    addressLibrary prev;
};

struct Library {
    addressLibrary head;
    addressLibrary tail;
};

struct NodePlaylist {
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
    addressPlaylist currentPlaylistNode;
};

void createLibrary(Library &L);
void createPlaylist(Playlist &P, string nama);
addressLibrary allocateLibrary(Song s);
addressPlaylist allocatePlaylist(Song s);
void addSong(Library &L, Song s);
void showAllSongs(Library L);
Song* findSongById(Library L, int id);
void updateSong(Library &L, int id, Song newData);
void deleteSong(Library &L, int id, Playlist playlists[], int &playlistCount);
void searchSong(Library L);
void playSong(Library L, CurrentPlay &cp, int id);
void stopSong(CurrentPlay &cp);
void nextSong(Library L, CurrentPlay &cp);
void prevSong(Library L, CurrentPlay &cp);
void addToPlaylist(Playlist &P, Song s);
void removeFromPlaylist(Playlist &P, int id);
void showPlaylist(Playlist P);
void playFromPlaylist(Playlist P, CurrentPlay &cp, int id);
void updateSongInPlaylist(Playlist &P, int id, Song newData);
void deleteSongFromPlaylist(Playlist &P, int id);
Song* findSimilarSong(Library L, Song current);

#endif /* musikinAza_h */
