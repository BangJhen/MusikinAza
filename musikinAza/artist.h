#ifndef artist_h
#define artist_h

#include "song.h"
#include "library.h"

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

void createArtistList(ArtistList &AL);
void addSongToArtist(ArtistList &AL, Song s);
void showAllArtists(ArtistList AL);
void showArtistAlbums(ArtistList AL, string namaArtis);
void showAlbumSongs(ArtistList AL, string namaArtis, string namaAlbum);

#endif
