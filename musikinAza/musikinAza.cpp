#include "musikinAza.h"

void createLibrary(Library &L) {
    L.first = nullptr;
    L.last = nullptr;
}

void createPlaylist(Playlist &P, string nama) {
    P.nama = nama;
    P.first = nullptr;
    P.last = nullptr;
}

addressLibrary allocateLibrary(Song s) {
    addressLibrary p = new elmLibrary;
    p->info = s;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

addressPlaylist allocatePlaylist(Song s) {
    addressPlaylist p = new elmPlaylist;
    p->info = s;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void addSong(Library &L, Song s) {
    addressLibrary p = allocateLibrary(s);
    
    if (L.first == nullptr) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
    }
    cout << "Lagu berhasil ditambahkan!" << endl;
}

void showAllSongs(Library L) {
    if (L.first == nullptr) {
        cout << "Library kosong." << endl;
    } else {
        addressLibrary p = L.first;
        cout << "\n=== DAFTAR LAGU ===" << endl;
        while (p != nullptr) {
            cout << "ID: " << p->info.id << endl;
            cout << "Judul: " << p->info.judul << endl;
            cout << "Artis: " << p->info.artis << endl;
            cout << "Album: " << p->info.album << endl;
            cout << "Genre: " << p->info.genre << endl;
            cout << "Tahun: " << p->info.tahun << endl;
            cout << "-------------------" << endl;
            p = p->next;
        }
    }
}

Song findSongById(Library L, int id) {
    addressLibrary p = L.first;
    while (p != nullptr) {
        if (p->info.id == id) {
            return p->info;
        }
        p = p->next;
    }
    Song notFound;
    notFound.id = -1;
    return notFound;
}

void updateSong(Library &L, int id, Song newData) {
    addressLibrary p = L.first;
    bool found = false;
    while (p != nullptr && !found) {
        if (p->info.id == id) {
            p->info.judul = newData.judul;
            p->info.artis = newData.artis;
            p->info.genre = newData.genre;
            p->info.tahun = newData.tahun;
            cout << "Lagu berhasil diupdate!" << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void deleteSong(Library &L, int id, Playlist playlists[], int &playlistCount) {
    addressLibrary p = L.first;
    bool found = false;
    
    while (p != nullptr && !found) {
        if (p->info.id == id) {
            if (p->prev == nullptr) {
                L.first = p->next;
                if (L.first != nullptr) {
                    L.first->prev = nullptr;
                }
            } else {
                p->prev->next = p->next;
            }
            
            if (p->next == nullptr) {
                L.last = p->prev;
                if (L.last != nullptr) {
                    L.last->next = nullptr;
                }
            } else {
                p->next->prev = p->prev;
            }
            
            for (int i = 0; i < playlistCount; i++) {
                deleteSongFromPlaylist(playlists[i], id);
            }
            
            delete p;
            cout << "Lagu berhasil dihapus dari library dan semua playlist!" << endl;
            found = true;
        } else {
            p = p->next;
        }
    }
    if (!found) {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void searchSong(Library L) {
    int pilihan;
    cout << "\nCari berdasarkan:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Judul" << endl;
    cout << "3. Artis" << endl;
    cout << "Pilihan: ";
    
    try {
        cin >> pilihan;
        if (cin.fail()) {
            throw runtime_error("Input tidak valid");
        }
        cin.ignore();
        
        addressLibrary p = L.first;
        bool found = false;
        
        if (pilihan == 1) {
            int id;
            cout << "Masukkan ID: ";
            cin >> id;
            if (cin.fail()) {
                throw runtime_error("ID harus angka");
            }
            while (p != nullptr) {
                if (p->info.id == id) {
                    cout << "\nLagu ditemukan:" << endl;
                    cout << "ID: " << p->info.id << endl;
                    cout << "Judul: " << p->info.judul << endl;
                    cout << "Artis: " << p->info.artis << endl;
                    cout << "Album: " << p->info.album << endl;
                    cout << "Genre: " << p->info.genre << endl;
                    cout << "Tahun: " << p->info.tahun << endl;
                    found = true;
                    break;
                }
                p = p->next;
            }
        } else if (pilihan == 2) {
            string judul;
            cout << "Masukkan judul: ";
            getline(cin, judul);
            while (p != nullptr) {
                if (p->info.judul.find(judul) != string::npos) {
                    cout << "\nLagu ditemukan:" << endl;
                    cout << "ID: " << p->info.id << endl;
                    cout << "Judul: " << p->info.judul << endl;
                    cout << "Artis: " << p->info.artis << endl;
                    cout << "Album: " << p->info.album << endl;
                    cout << "Genre: " << p->info.genre << endl;
                    cout << "Tahun: " << p->info.tahun << endl;
                    cout << "-------------------" << endl;
                    found = true;
                }
                p = p->next;
            }
        } else if (pilihan == 3) {
            string artis;
            cout << "Masukkan artis: ";
            getline(cin, artis);
            while (p != nullptr) {
                if (p->info.artis.find(artis) != string::npos) {
                    cout << "\nLagu ditemukan:" << endl;
                    cout << "ID: " << p->info.id << endl;
                    cout << "Judul: " << p->info.judul << endl;
                    cout << "Artis: " << p->info.artis << endl;
                    cout << "Album: " << p->info.album << endl;
                    cout << "Genre: " << p->info.genre << endl;
                    cout << "Tahun: " << p->info.tahun << endl;
                    cout << "-------------------" << endl;
                    found = true;
                }
                p = p->next;
            }
        }
        
        if (!found) {
            cout << "Lagu tidak ditemukan." << endl;
        }
    } catch (exception &e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void playSong(Library L, CurrentPlay &cp, int id) {
    Song s = findSongById(L, id);
    if (s.id != -1) {
        cp.info = s;
        cp.isPlaying = true;
        cp.fromPlaylist = false;
        cp.currentPlaylistelm = nullptr;
        cout << "\nSekarang memutar: " << s.judul << " - " << s.artis << endl;
    } else {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void stopSong(CurrentPlay &cp) {
    if (cp.isPlaying) {
        cout << "\nLagu " << cp.info.judul << " dihentikan." << endl;
        cp.isPlaying = false;
    } else {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
    }
}

Song findSimilarSong(Library L, Song current) {
    addressLibrary p = L.first;
    addressLibrary sameArtist = nullptr;
    addressLibrary sameGenre = nullptr;
    
    while (p != nullptr) {
        if (p->info.id != current.id) {
            if (p->info.artis == current.artis && sameArtist == nullptr) {
                sameArtist = p;
            }
            if (p->info.genre == current.genre && sameGenre == nullptr) {
                sameGenre = p;
            }
        }
        p = p->next;
    }
    
    if (sameArtist != nullptr) {
        return sameArtist->info;
    } else if (sameGenre != nullptr) {
        return sameGenre->info;
    }
    Song notFound;
    notFound.id = -1;
    return notFound;
}

void nextSong(Library L, CurrentPlay &cp) {
    if (!cp.isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
    } else if (cp.fromPlaylist && cp.currentPlaylistelm != nullptr) {
        if (cp.currentPlaylistelm->next != nullptr) {
            cp.currentPlaylistelm = cp.currentPlaylistelm->next;
            cp.info = cp.currentPlaylistelm->info;
            cout << "\nNext: " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Sudah di akhir playlist." << endl;
        }
    } else {
        Song similar = findSimilarSong(L, cp.info);
        if (similar.id != -1) {
            cp.info = similar;
            cout << "\nNext (lagu mirip): " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Tidak ada lagu mirip yang ditemukan." << endl;
        }
    }
}

void prevSong(Library L, CurrentPlay &cp) {
    if (!cp.isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
    } else if (cp.fromPlaylist && cp.currentPlaylistelm != nullptr) {
        if (cp.currentPlaylistelm->prev != nullptr) {
            cp.currentPlaylistelm = cp.currentPlaylistelm->prev;
            cp.info = cp.currentPlaylistelm->info;
            cout << "\nPrev: " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Sudah di awal playlist." << endl;
        }
    } else {
        Song similar = findSimilarSong(L, cp.info);
        if (similar.id != -1) {
            cp.info = similar;
            cout << "\nPrev (lagu mirip): " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Tidak ada lagu mirip yang ditemukan." << endl;
        }
    }
}

void addToPlaylist(Playlist &P, Song s) {
    addressPlaylist p = allocatePlaylist(s);
    
    if (P.first == nullptr) {
        P.first = p;
        P.last = p;
    } else {
        P.last->next = p;
        p->prev = P.last;
        P.last = p;
    }
    cout << "Lagu ditambahkan ke playlist!" << endl;
}

void removeFromPlaylist(Playlist &P, int id) {
    if (P.first == nullptr) {
        cout << "Playlist kosong." << endl;
    } else {
        addressPlaylist p = P.first;
        bool found = false;
        
        while (p != nullptr && !found) {
            if (p->info.id == id) {
                if (p->prev == nullptr) {
                    P.first = p->next;
                    if (P.first != nullptr) {
                        P.first->prev = nullptr;
                    }
                } else {
                    p->prev->next = p->next;
                }
                
                if (p->next == nullptr) {
                    P.last = p->prev;
                    if (P.last != nullptr) {
                        P.last->next = nullptr;
                    }
                } else {
                    p->next->prev = p->prev;
                }
                
                delete p;
                cout << "Lagu dihapus dari playlist!" << endl;
                found = true;
            } else {
                p = p->next;
            }
        }
        if (!found) {
            cout << "Lagu tidak ditemukan di playlist." << endl;
        }
    }
}

void showPlaylist(Playlist P) {
    if (P.first == nullptr) {
        cout << "Playlist kosong." << endl;
    } else {
        addressPlaylist p = P.first;
        cout << "\n=== PLAYLIST: " << P.nama << " ===" << endl;
        while (p != nullptr) {
            cout << "ID: " << p->info.id << endl;
            cout << "Judul: " << p->info.judul << endl;
            cout << "Artis: " << p->info.artis << endl;
            cout << "Genre: " << p->info.genre << endl;
            cout << "Tahun: " << p->info.tahun << endl;
            cout << "-------------------" << endl;
            p = p->next;
        }
    }
}

void playFromPlaylist(Playlist P, CurrentPlay &cp, int id) {
    addressPlaylist p = P.first;
    bool found = false;
    while (p != nullptr && !found) {
        if (p->info.id == id) {
            cp.info = p->info;
            cp.isPlaying = true;
            cp.fromPlaylist = true;
            cp.currentPlaylistelm = p;
            cout << "\nSekarang memutar dari playlist: " << p->info.judul << " - " << p->info.artis << endl;
            found = true;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Lagu tidak ditemukan di playlist." << endl;
    }
}

void updateSongInPlaylist(Playlist &P, int id, Song newData) {
    addressPlaylist p = P.first;
    bool found = false;
    while (p != nullptr && !found) {
        if (p->info.id == id) {
            p->info.judul = newData.judul;
            p->info.artis = newData.artis;
            p->info.genre = newData.genre;
            p->info.tahun = newData.tahun;
            found = true;
        }
        p = p->next;
    }
}

void deleteSongFromPlaylist(Playlist &P, int id) {
    if (P.first != nullptr) {
        addressPlaylist p = P.first;
        bool found = false;
        
        while (p != nullptr && !found) {
            if (p->info.id == id) {
                if (p->prev == nullptr) {
                    P.first = p->next;
                    if (P.first != nullptr) {
                        P.first->prev = nullptr;
                    }
                } else {
                    p->prev->next = p->next;
                }
                
                if (p->next == nullptr) {
                    P.last = p->prev;
                    if (P.last != nullptr) {
                        P.last->next = nullptr;
                    }
                } else {
                    p->next->prev = p->prev;
                }
                
                delete p;
                found = true;
            } else {
                p = p->next;
            }
        }
    }
}

void createQueue(PlayQueue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

void enqueueSong(PlayQueue &Q, Song s) {
    addressQueue p = new elmQueue;
    p->info = s;
    p->next = nullptr;
    
    if (Q.head == nullptr) {
        Q.head = p;
        Q.tail = p;
    } else {
        Q.tail->next = p;
        Q.tail = p;
    }
    cout << "Lagu ditambahkan ke antrian!" << endl;
}

void dequeueSong(PlayQueue &Q, Song &s) {
    if (Q.head != nullptr) {
        addressQueue p = Q.head;
        s = p->info;
        Q.head = p->next;
        if (Q.head == nullptr) {
            Q.tail = nullptr;
        }
        delete p;
    }
}

void showQueue(PlayQueue Q) {
    if (Q.head == nullptr) {
        cout << "Antrian kosong." << endl;
    } else {
        addressQueue p = Q.head;
        int no = 1;
        cout << "\n=== ANTRIAN PEMUTARAN ===" << endl;
        while (p != nullptr) {
            cout << no++ << ". " << p->info.judul << " - " << p->info.artis << endl;
            p = p->next;
        }
    }
}

bool isQueueEmpty(PlayQueue Q) {
    return Q.head == nullptr;
}

void createHistory(History &H) {
    H.top = nullptr;
}

void pushHistory(History &H, Song s) {
    addressHistory p = new elmHistory;
    p->info = s;
    p->next = H.top;
    H.top = p;
}

void popHistory(History &H, Song &s) {
    if (H.top != nullptr) {
        addressHistory p = H.top;
        s = p->info;
        H.top = p->next;
        delete p;
    }
}

void showHistory(History H) {
    if (H.top == nullptr) {
        cout << "Riwayat kosong." << endl;
    } else {
        addressHistory p = H.top;
        int no = 1;
        cout << "\n=== RIWAYAT PEMUTARAN ===" << endl;
        while (p != nullptr && no <= 10) {
            cout << no++ << ". " << p->info.judul << " - " << p->info.artis << endl;
            p = p->next;
        }
    }
}

bool isHistoryEmpty(History H) {
    return H.top == nullptr;
}

void createArtistList(ArtistList &AL) {
    AL.first = nullptr;
}

void addSongToArtist(ArtistList &AL, Song s) {
    addressArtist currArtist = AL.first;
    addressArtist prevArtist = nullptr;
    
    while (currArtist != nullptr && currArtist->namaArtis != s.artis) {
        prevArtist = currArtist;
        currArtist = currArtist->next;
    }
    
    if (currArtist == nullptr) {
        currArtist = new elmArtist;
        currArtist->namaArtis = s.artis;
        currArtist->albums = nullptr;
        currArtist->next = nullptr;
        
        if (AL.first == nullptr) {
            AL.first = currArtist;
        } else {
            prevArtist->next = currArtist;
        }
    }
    
    addressAlbum currAlbum = currArtist->albums;
    addressAlbum prevAlbum = nullptr;
    
    while (currAlbum != nullptr && currAlbum->namaAlbum != s.album) {
        prevAlbum = currAlbum;
        currAlbum = currAlbum->next;
    }
    
    if (currAlbum == nullptr) {
        currAlbum = new elmAlbum;
        currAlbum->namaAlbum = s.album;
        currAlbum->songs = nullptr;
        currAlbum->next = nullptr;
        
        if (currArtist->albums == nullptr) {
            currArtist->albums = currAlbum;
        } else {
            prevAlbum->next = currAlbum;
        }
    }
    
    addressLibrary newSong = new elmLibrary;
    newSong->info = s;
    newSong->next = currAlbum->songs;
    newSong->prev = nullptr;
    if (currAlbum->songs != nullptr) {
        currAlbum->songs->prev = newSong;
    }
    currAlbum->songs = newSong;
}

void showAllArtists(ArtistList AL) {
    if (AL.first == nullptr) {
        cout << "Belum ada artis." << endl;
    } else {
        addressArtist p = AL.first;
        cout << "\n=== DAFTAR ARTIS ===" << endl;
        while (p != nullptr) {
            cout << "- " << p->namaArtis << endl;
            p = p->next;
        }
    }
}

void showArtistAlbums(ArtistList AL, string namaArtis) {
    addressArtist p = AL.first;
    
    while (p != nullptr && p->namaArtis != namaArtis) {
        p = p->next;
    }
    
    if (p == nullptr) {
        cout << "Artis tidak ditemukan." << endl;
    } else if (p->albums == nullptr) {
        cout << "Artis belum memiliki album." << endl;
    } else {
        addressAlbum album = p->albums;
        cout << "\n=== ALBUM " << namaArtis << " ===" << endl;
        while (album != nullptr) {
            cout << "- " << album->namaAlbum << endl;
            album = album->next;
        }
    }
}

void showAlbumSongs(ArtistList AL, string namaArtis, string namaAlbum) {
    addressArtist artist = AL.first;
    
    while (artist != nullptr && artist->namaArtis != namaArtis) {
        artist = artist->next;
    }
    
    if (artist == nullptr) {
        cout << "Artis tidak ditemukan." << endl;
    } else {
        addressAlbum album = artist->albums;
        while (album != nullptr && album->namaAlbum != namaAlbum) {
            album = album->next;
        }
        
        if (album == nullptr) {
            cout << "Album tidak ditemukan." << endl;
        } else if (album->songs == nullptr) {
            cout << "Album belum memiliki lagu." << endl;
        } else {
            addressLibrary song = album->songs;
            cout << "\n=== LAGU DI ALBUM " << namaAlbum << " ===" << endl;
            while (song != nullptr) {
                cout << "ID: " << song->info.id << " - " << song->info.judul << endl;
                song = song->next;
            }
        }
    }
}

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
