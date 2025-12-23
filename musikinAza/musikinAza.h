#ifndef musikinAza_h
#define musikinAza_h

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

struct Song {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
    string album;
};

typedef struct elmLibrary* addressLibrary;

struct elmLibrary {
    Song info;
    addressLibrary next;
    addressLibrary prev;
};

struct Library {
    addressLibrary first;
    addressLibrary last;
};

typedef struct elmPlaylist* addressPlaylist;

struct elmPlaylist {
    Song info;
    addressPlaylist next;
    addressPlaylist prev;
};

struct Playlist {
    string nama;
    addressPlaylist first;
    addressPlaylist last;
};

struct CurrentPlay {
    Song info;
    bool isPlaying;
    bool fromPlaylist;
    addressPlaylist currentPlaylistelm;
};

typedef struct elmQueue* addressQueue;

struct elmQueue {
    Song info;
    addressQueue next;
};

struct PlayQueue {
    addressQueue head;
    addressQueue tail;
};

typedef struct elmHistory* addressHistory;

struct elmHistory {
    Song info;
    addressHistory next;
};

struct History {
    addressHistory top;
};

typedef struct elmAlbum* addressAlbum;
typedef struct elmArtist* addressArtist;

struct elmAlbum {
    string namaAlbum;
    addressLibrary songs;
    addressAlbum next;
};

struct elmArtist {
    string namaArtis;
    addressAlbum albums;
    addressArtist next;
};

struct ArtistList {
    addressArtist first;
};

void createLibrary(Library &L);
addressLibrary allocateLibrary(Song s);
void addSong(Library &L, Song s);
void showAllSongs(Library L);
Song findSongById(Library L, int id);
void updateSong(Library &L, int id, Song newData);
void deleteSong(Library &L, int id, Playlist playlists[], int &playlistCount);
void searchSong(Library L);
Song findSimilarSong(Library L, Song current);

void createPlaylist(Playlist &P, string nama);
addressPlaylist allocatePlaylist(Song s);
void addToPlaylist(Playlist &P, Song s);
void removeFromPlaylist(Playlist &P, int id);
void showPlaylist(Playlist P);
void playFromPlaylist(Playlist P, CurrentPlay &cp, int id);
void updateSongInPlaylist(Playlist &P, int id, Song newData);
void deleteSongFromPlaylist(Playlist &P, int id);
void deletePlaylist(Playlist playlists[], int &playlistCount, int index);

void playSong(Library L, CurrentPlay &cp, int id);
void stopSong(CurrentPlay &cp);
void nextSong(Library L, CurrentPlay &cp);
void prevSong(Library L, CurrentPlay &cp);

void createQueue(PlayQueue &Q);
void enqueueSong(PlayQueue &Q, Song s);
void dequeueSong(PlayQueue &Q, Song &s);
void showQueue(PlayQueue Q);
bool isQueueEmpty(PlayQueue Q);

void createHistory(History &H);
void pushHistory(History &H, Song s);
void popHistory(History &H, Song &s);
void showHistory(History H);
bool isHistoryEmpty(History H);

void createArtistList(ArtistList &AL);
void addSongToArtist(ArtistList &AL, Song s);
void showAllArtists(ArtistList AL);
void showArtistAlbums(ArtistList AL, string namaArtis);
void showAlbumSongs(ArtistList AL, string namaArtis, string namaAlbum);

void loadDummyData(Library &L, ArtistList &AL);

#endif
