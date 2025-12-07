#ifndef musikinAza_h
#define musikinAza_h

#include <iostream>
#include <string>
using namespace std;

typedef struct elmLibrary* addressLibrary;
typedef struct elmPlaylist* addressPlaylist;
typedef struct elmQueue* addressQueue;
typedef struct elmHistory* addressHistory;
typedef struct elmAlbum* addressAlbum;
typedef struct elmArtist* addressArtist;

struct Song {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
    string album;
};

struct elmLibrary {
    Song info;
    addressLibrary next;
    addressLibrary prev;
};

struct Library {
    addressLibrary head;
    addressLibrary tail;
};

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

struct elmQueue {
    Song info;
    addressQueue next;
};

struct PlayQueue {
    addressQueue head;
    addressQueue tail;
};

struct elmHistory {
    Song info;
    addressHistory next;
};

struct History {
    addressHistory top;
};

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
    addressArtist head;
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

#endif /* musikinAza_h */
