#include "musikinAza.h"

void createLibrary(Library &L) {
    L.head = nullptr;
    L.tail = nullptr;
}

void createPlaylist(Playlist &P, string nama) {
    P.nama = nama;
    P.head = nullptr;
    P.tail = nullptr;
}

addressLibrary allocateLibrary(Song s) {
    addressLibrary p = new NodeLibrary;
    p->info = s;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

addressPlaylist allocatePlaylist(Song s) {
    addressPlaylist p = new NodePlaylist;
    p->info = s;
    p->next = nullptr;
    return p;
}

void addSong(Library &L, Song s) {
    addressLibrary p = allocateLibrary(s);
    
    if (L.head == nullptr) {
        L.head = p;
        L.tail = p;
    } else {
        L.tail->next = p;
        p->prev = L.tail;
        L.tail = p;
    }
    cout << "Lagu berhasil ditambahkan!" << endl;
}

void showAllSongs(Library L) {
    if (L.head == nullptr) {
        cout << "Library kosong." << endl;
        return;
    }
    
    addressLibrary p = L.head;
    cout << "\n=== DAFTAR LAGU ===" << endl;
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

Song* findSongById(Library L, int id) {
    addressLibrary p = L.head;
    while (p != nullptr) {
        if (p->info.id == id) {
            return &(p->info);
        }
        p = p->next;
    }
    return nullptr;
}

void updateSong(Library &L, int id, Song newData) {
    addressLibrary p = L.head;
    while (p != nullptr) {
        if (p->info.id == id) {
            p->info.judul = newData.judul;
            p->info.artis = newData.artis;
            p->info.genre = newData.genre;
            p->info.tahun = newData.tahun;
            cout << "Lagu berhasil diupdate!" << endl;
            return;
        }
        p = p->next;
    }
    cout << "Lagu tidak ditemukan." << endl;
}

void deleteSong(Library &L, int id, Playlist playlists[], int &playlistCount) {
    addressLibrary p = L.head;
    
    while (p != nullptr) {
        if (p->info.id == id) {
            if (p->prev == nullptr) {
                L.head = p->next;
                if (L.head != nullptr) {
                    L.head->prev = nullptr;
                }
            } else {
                p->prev->next = p->next;
            }
            
            if (p->next == nullptr) {
                L.tail = p->prev;
                if (L.tail != nullptr) {
                    L.tail->next = nullptr;
                }
            } else {
                p->next->prev = p->prev;
            }
            
            for (int i = 0; i < playlistCount; i++) {
                deleteSongFromPlaylist(playlists[i], id);
            }
            
            delete p;
            cout << "Lagu berhasil dihapus dari library dan semua playlist!" << endl;
            return;
        }
        p = p->next;
    }
    cout << "Lagu tidak ditemukan." << endl;
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
        
        addressLibrary p = L.head;
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
    Song* s = findSongById(L, id);
    if (s != nullptr) {
        cp.info = *s;
        cp.isPlaying = true;
        cp.fromPlaylist = false;
        cp.currentPlaylistNode = nullptr;
        cout << "\nSekarang memutar: " << s->judul << " - " << s->artis << endl;
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

Song* findSimilarSong(Library L, Song current) {
    addressLibrary p = L.head;
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
        return &(sameArtist->info);
    } else if (sameGenre != nullptr) {
        return &(sameGenre->info);
    }
    return nullptr;
}

void nextSong(Library L, CurrentPlay &cp) {
    if (!cp.isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
        return;
    }
    
    if (cp.fromPlaylist && cp.currentPlaylistNode != nullptr) {
        if (cp.currentPlaylistNode->next != nullptr) {
            cp.currentPlaylistNode = cp.currentPlaylistNode->next;
            cp.info = cp.currentPlaylistNode->info;
            cout << "\nNext: " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Sudah di akhir playlist." << endl;
        }
    } else {
        Song* similar = findSimilarSong(L, cp.info);
        if (similar != nullptr) {
            cp.info = *similar;
            cout << "\nNext (lagu mirip): " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Tidak ada lagu mirip yang ditemukan." << endl;
        }
    }
}

void prevSong(Library L, CurrentPlay &cp) {
    if (!cp.isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
        return;
    }
    
    if (cp.fromPlaylist && cp.currentPlaylistNode != nullptr) {
        cout << "Fitur prev di playlist tidak tersedia (singly linked list)." << endl;
    } else {
        Song* similar = findSimilarSong(L, cp.info);
        if (similar != nullptr) {
            cp.info = *similar;
            cout << "\nPrev (lagu mirip): " << cp.info.judul << " - " << cp.info.artis << endl;
        } else {
            cout << "Tidak ada lagu mirip yang ditemukan." << endl;
        }
    }
}

void addToPlaylist(Playlist &P, Song s) {
    addressPlaylist p = allocatePlaylist(s);
    
    if (P.head == nullptr) {
        P.head = p;
        P.tail = p;
    } else {
        P.tail->next = p;
        P.tail = p;
    }
    cout << "Lagu ditambahkan ke playlist!" << endl;
}

void removeFromPlaylist(Playlist &P, int id) {
    if (P.head == nullptr) {
        cout << "Playlist kosong." << endl;
        return;
    }
    
    addressPlaylist p = P.head;
    addressPlaylist prev = nullptr;
    
    while (p != nullptr) {
        if (p->info.id == id) {
            if (prev == nullptr) {
                P.head = p->next;
                if (P.head == nullptr) {
                    P.tail = nullptr;
                }
            } else {
                prev->next = p->next;
                if (p->next == nullptr) {
                    P.tail = prev;
                }
            }
            delete p;
            cout << "Lagu dihapus dari playlist!" << endl;
            return;
        }
        prev = p;
        p = p->next;
    }
    cout << "Lagu tidak ditemukan di playlist." << endl;
}

void showPlaylist(Playlist P) {
    if (P.head == nullptr) {
        cout << "Playlist kosong." << endl;
        return;
    }
    
    addressPlaylist p = P.head;
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

void playFromPlaylist(Playlist P, CurrentPlay &cp, int id) {
    addressPlaylist p = P.head;
    while (p != nullptr) {
        if (p->info.id == id) {
            cp.info = p->info;
            cp.isPlaying = true;
            cp.fromPlaylist = true;
            cp.currentPlaylistNode = p;
            cout << "\nSekarang memutar dari playlist: " << p->info.judul << " - " << p->info.artis << endl;
            return;
        }
        p = p->next;
    }
    cout << "Lagu tidak ditemukan di playlist." << endl;
}

void updateSongInPlaylist(Playlist &P, int id, Song newData) {
    addressPlaylist p = P.head;
    while (p != nullptr) {
        if (p->info.id == id) {
            p->info.judul = newData.judul;
            p->info.artis = newData.artis;
            p->info.genre = newData.genre;
            p->info.tahun = newData.tahun;
            return;
        }
        p = p->next;
    }
}

void deleteSongFromPlaylist(Playlist &P, int id) {
    if (P.head == nullptr) {
        return;
    }
    
    addressPlaylist p = P.head;
    addressPlaylist prev = nullptr;
    
    while (p != nullptr) {
        if (p->info.id == id) {
            if (prev == nullptr) {
                P.head = p->next;
                if (P.head == nullptr) {
                    P.tail = nullptr;
                }
            } else {
                prev->next = p->next;
                if (p->next == nullptr) {
                    P.tail = prev;
                }
            }
            delete p;
            return;
        }
        prev = p;
        p = p->next;
    }
}
