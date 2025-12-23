#include "musikinAza.h"

void loadDummyData(Library &L, ArtistList &AL) {
    Song s1, s2, s3, s4, s5, s6, s7, s8;
    
    s1.id = 1;
    s1.judul = "Bohemian Rhapsody";
    s1.artis = "Queen";
    s1.album = "A Night at the Opera";
    s1.genre = "Rock";
    s1.tahun = 1975;
    addSong(L, s1);
    addSongToArtist(AL, s1);
    
    s2.id = 2;
    s2.judul = "We Will Rock You";
    s2.artis = "Queen";
    s2.album = "News of the World";
    s2.genre = "Rock";
    s2.tahun = 1977;
    addSong(L, s2);
    addSongToArtist(AL, s2);
    
    s3.id = 3;
    s3.judul = "Imagine";
    s3.artis = "John Lennon";
    s3.album = "Imagine";
    s3.genre = "Pop";
    s3.tahun = 1971;
    addSong(L, s3);
    addSongToArtist(AL, s3);
    
    s4.id = 4;
    s4.judul = "Stairway to Heaven";
    s4.artis = "Led Zeppelin";
    s4.album = "Led Zeppelin IV";
    s4.genre = "Rock";
    s4.tahun = 1971;
    addSong(L, s4);
    addSongToArtist(AL, s4);
    
    s5.id = 5;
    s5.judul = "Hotel California";
    s5.artis = "Eagles";
    s5.album = "Hotel California";
    s5.genre = "Rock";
    s5.tahun = 1976;
    addSong(L, s5);
    addSongToArtist(AL, s5);
    
    s6.id = 6;
    s6.judul = "Billie Jean";
    s6.artis = "Michael Jackson";
    s6.album = "Thriller";
    s6.genre = "Pop";
    s6.tahun = 1982;
    addSong(L, s6);
    addSongToArtist(AL, s6);
    
    s7.id = 7;
    s7.judul = "Smells Like Teen Spirit";
    s7.artis = "Nirvana";
    s7.album = "Nevermind";
    s7.genre = "Grunge";
    s7.tahun = 1991;
    addSong(L, s7);
    addSongToArtist(AL, s7);
    
    s8.id = 8;
    s8.judul = "Sweet Child O' Mine";
    s8.artis = "Guns N' Roses";
    s8.album = "Appetite for Destruction";
    s8.genre = "Rock";
    s8.tahun = 1987;
    addSong(L, s8);
    addSongToArtist(AL, s8);
    
    cout << "\n=== Data dummy berhasil dimuat! ===" << endl;
    cout << "Total 8 lagu telah ditambahkan ke library." << endl;
}
