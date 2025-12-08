#include <iostream>
#include "musikinAza.h"

using namespace std;

void menuAdmin(Library &L, Playlist playlists[], int &playlistCount, ArtistList &AL) {
    int pilihan;
    do {
        cout << "\n=== MENU ADMIN ===" << endl;
        cout << "1. Tambah Lagu" << endl;
        cout << "2. Lihat Semua Lagu" << endl;
        cout << "3. Update Lagu" << endl;
        cout << "4. Hapus Lagu" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        
        try {
            cin >> pilihan;
            if (cin.fail()) {
                throw runtime_error("Input tidak valid");
            }
            cin.ignore();
            
            if (pilihan == 1) {
                Song s;
                cout << "\nMasukkan ID: ";
                cin >> s.id;
                if (cin.fail()) {
                    throw runtime_error("ID harus angka");
                }
                cin.ignore();
                cout << "Masukkan Judul: ";
                getline(cin, s.judul);
                cout << "Masukkan Artis: ";
                getline(cin, s.artis);
                cout << "Masukkan Album: ";
                getline(cin, s.album);
                cout << "Masukkan Genre: ";
                getline(cin, s.genre);
                cout << "Masukkan Tahun: ";
                cin >> s.tahun;
                if (cin.fail()) {
                    throw runtime_error("Tahun harus angka");
                }
                addSong(L, s);
                addSongToArtist(AL, s);
            } else if (pilihan == 2) {
                showAllSongs(L);
            } else if (pilihan == 3) {
                int id;
                cout << "\nMasukkan ID lagu yang akan diupdate: ";
                cin >> id;
                if (cin.fail()) {
                    throw runtime_error("ID harus angka");
                }
                cin.ignore();
                
                Song* existing = findSongById(L, id);
                if (existing != nullptr) {
                    Song newData;
                    newData.id = id;
                    cout << "Judul baru: ";
                    getline(cin, newData.judul);
                    cout << "Artis baru: ";
                    getline(cin, newData.artis);
                    cout << "Genre baru: ";
                    getline(cin, newData.genre);
                    cout << "Tahun baru: ";
                    cin >> newData.tahun;
                    if (cin.fail()) {
                        throw runtime_error("Tahun harus angka");
                    }
                    
                    updateSong(L, id, newData);
                    
                    for (int i = 0; i < playlistCount; i++) {
                        updateSongInPlaylist(playlists[i], id, newData);
                    }
                } else {
                    cout << "Lagu tidak ditemukan." << endl;
                }
            } else if (pilihan == 4) {
                int id;
                cout << "\nMasukkan ID lagu yang akan dihapus: ";
                cin >> id;
                if (cin.fail()) {
                    throw runtime_error("ID harus angka");
                }
                deleteSong(L, id, playlists, playlistCount);
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }
    } while (pilihan != 0);
}

void menuUser(Library &L, Playlist playlists[], int &playlistCount, CurrentPlay &cp, PlayQueue &Q, History &H, ArtistList &AL) {
    int pilihan;
    do {
        cout << "\n=== MENU USER ===" << endl;
        cout << "1. Cari Lagu" << endl;
        cout << "2. Putar Lagu dari Library" << endl;
        cout << "3. Stop Lagu" << endl;
        cout << "4. Next Lagu" << endl;
        cout << "5. Prev Lagu" << endl;
        cout << "6. Kelola Playlist" << endl;
        cout << "7. Antrian Pemutaran" << endl;
        cout << "8. Riwayat Pemutaran" << endl;
        cout << "9. Browse by Artis" << endl;
        cout << "10. Lihat Semua Lagu" << endl;
        cout << "0. Kembali" << endl;
        cout << "Pilihan: ";
        
        try {
            cin >> pilihan;
            if (cin.fail()) {
                throw runtime_error("Input tidak valid");
            }
            
            if (pilihan == 1) {
                searchSong(L);
            } else if (pilihan == 2) {
                int id;
                cout << "Masukkan ID lagu: ";
                cin >> id;
                if (cin.fail()) {
                    throw runtime_error("ID harus angka");
                }
                playSong(L, cp, id);
                if (cp.isPlaying) {
                    pushHistory(H, cp.info);
                }
            } else if (pilihan == 3) {
                stopSong(cp);
            } else if (pilihan == 4) {
                nextSong(L, cp);
                if (cp.isPlaying) {
                    pushHistory(H, cp.info);
                }
            } else if (pilihan == 5) {
                prevSong(L, cp);
                if (cp.isPlaying) {
                    pushHistory(H, cp.info);
                }
            } else if (pilihan == 6) {
                int pilihanPlaylist;
                do {
                    cout << "\n=== KELOLA PLAYLIST ===" << endl;
                    cout << "1. Buat Playlist Baru" << endl;
                    cout << "2. Tambah Lagu ke Playlist" << endl;
                    cout << "3. Hapus Lagu dari Playlist" << endl;
                    cout << "4. Lihat Playlist" << endl;
                    cout << "5. Putar Lagu dari Playlist" << endl;
                    cout << "0. Kembali" << endl;
                    cout << "Pilihan: ";
                    
                    try {
                        cin >> pilihanPlaylist;
                        if (cin.fail()) {
                            throw runtime_error("Input tidak valid");
                        }
                        cin.ignore();
                        
                        if (pilihanPlaylist == 1) {
                            if (playlistCount < 10) {
                                string nama;
                                cout << "Nama playlist: ";
                                getline(cin, nama);
                                createPlaylist(playlists[playlistCount], nama);
                                playlistCount++;
                                cout << "Playlist berhasil dibuat!" << endl;
                            } else {
                                cout << "Maksimal 10 playlist." << endl;
                            }
                        } else if (pilihanPlaylist == 2) {
                            if (playlistCount == 0) {
                                cout << "Belum ada playlist." << endl;
                            } else {
                                cout << "\nDaftar Playlist:" << endl;
                                for (int i = 0; i < playlistCount; i++) {
                                    cout << i + 1 << ". " << playlists[i].nama << endl;
                                }
                                int idx;
                                cout << "Pilih playlist: ";
                                cin >> idx;
                                if (cin.fail()) {
                                    throw runtime_error("Input harus angka");
                                }
                                if (idx > 0 && idx <= playlistCount) {
                                    int id;
                                    cout << "Masukkan ID lagu: ";
                                    cin >> id;
                                    if (cin.fail()) {
                                        throw runtime_error("ID harus angka");
                                    }
                                    Song* s = findSongById(L, id);
                                    if (s != nullptr) {
                                        addToPlaylist(playlists[idx - 1], *s);
                                    } else {
                                        cout << "Lagu tidak ditemukan." << endl;
                                    }
                                }
                            }
                        } else if (pilihanPlaylist == 3) {
                            if (playlistCount == 0) {
                                cout << "Belum ada playlist." << endl;
                            } else {
                                cout << "\nDaftar Playlist:" << endl;
                                for (int i = 0; i < playlistCount; i++) {
                                    cout << i + 1 << ". " << playlists[i].nama << endl;
                                }
                                int idx;
                                cout << "Pilih playlist: ";
                                cin >> idx;
                                if (cin.fail()) {
                                    throw runtime_error("Input harus angka");
                                }
                                if (idx > 0 && idx <= playlistCount) {
                                    int id;
                                    cout << "Masukkan ID lagu: ";
                                    cin >> id;
                                    if (cin.fail()) {
                                        throw runtime_error("ID harus angka");
                                    }
                                    removeFromPlaylist(playlists[idx - 1], id);
                                }
                            }
                        } else if (pilihanPlaylist == 4) {
                            if (playlistCount == 0) {
                                cout << "Belum ada playlist." << endl;
                            } else {
                                cout << "\nDaftar Playlist:" << endl;
                                for (int i = 0; i < playlistCount; i++) {
                                    cout << i + 1 << ". " << playlists[i].nama << endl;
                                }
                                int idx;
                                cout << "Pilih playlist: ";
                                cin >> idx;
                                if (cin.fail()) {
                                    throw runtime_error("Input harus angka");
                                }
                                if (idx > 0 && idx <= playlistCount) {
                                    showPlaylist(playlists[idx - 1]);
                                }
                            }
                        } else if (pilihanPlaylist == 5) {
                            if (playlistCount == 0) {
                                cout << "Belum ada playlist." << endl;
                            } else {
                                cout << "\nDaftar Playlist:" << endl;
                                for (int i = 0; i < playlistCount; i++) {
                                    cout << i + 1 << ". " << playlists[i].nama << endl;
                                }
                                int idx;
                                cout << "Pilih playlist: ";
                                cin >> idx;
                                if (cin.fail()) {
                                    throw runtime_error("Input harus angka");
                                }
                                if (idx > 0 && idx <= playlistCount) {
                                    int id;
                                    cout << "Masukkan ID lagu: ";
                                    cin >> id;
                                    if (cin.fail()) {
                                        throw runtime_error("ID harus angka");
                                    }
                                    playFromPlaylist(playlists[idx - 1], cp, id);
                                }
                            }
                        }
                    } catch (exception &e) {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        pilihanPlaylist = -1;
                    }
                } while (pilihanPlaylist != 0);
            } else if (pilihan == 7) {
                int pilihanQueue;
                do {
                    cout << "\n=== ANTRIAN PEMUTARAN ===" << endl;
                    cout << "1. Tambah Lagu ke Antrian" << endl;
                    cout << "2. Lihat Antrian" << endl;
                    cout << "3. Putar dari Antrian" << endl;
                    cout << "0. Kembali" << endl;
                    cout << "Pilihan: ";
                    
                    try {
                        cin >> pilihanQueue;
                        if (cin.fail()) {
                            throw runtime_error("Input tidak valid");
                        }
                        
                        if (pilihanQueue == 1) {
                            int id;
                            cout << "Masukkan ID lagu: ";
                            cin >> id;
                            if (cin.fail()) {
                                throw runtime_error("ID harus angka");
                            }
                            Song* s = findSongById(L, id);
                            if (s != nullptr) {
                                enqueueSong(Q, *s);
                            } else {
                                cout << "Lagu tidak ditemukan." << endl;
                            }
                        } else if (pilihanQueue == 2) {
                            showQueue(Q);
                        } else if (pilihanQueue == 3) {
                            if (!isQueueEmpty(Q)) {
                                Song s;
                                dequeueSong(Q, s);
                                cp.info = s;
                                cp.isPlaying = true;
                                cp.fromPlaylist = false;
                                cp.currentPlaylistelm = nullptr;
                                pushHistory(H, s);
                                cout << "\nSekarang memutar dari antrian: " << s.judul << " - " << s.artis << endl;
                            } else {
                                cout << "Antrian kosong." << endl;
                            }
                        }
                    } catch (exception &e) {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        pilihanQueue = -1;
                    }
                } while (pilihanQueue != 0);
            } else if (pilihan == 8) {
                int pilihanHistory;
                do {
                    cout << "\n=== RIWAYAT PEMUTARAN ===" << endl;
                    cout << "1. Lihat Riwayat" << endl;
                    cout << "2. Putar dari Riwayat" << endl;
                    cout << "0. Kembali" << endl;
                    cout << "Pilihan: ";
                    
                    try {
                        cin >> pilihanHistory;
                        if (cin.fail()) {
                            throw runtime_error("Input tidak valid");
                        }
                        
                        if (pilihanHistory == 1) {
                            showHistory(H);
                        } else if (pilihanHistory == 2) {
                            if (!isHistoryEmpty(H)) {
                                showHistory(H);
                                int no;
                                cout << "Pilih nomor lagu: ";
                                cin >> no;
                                if (cin.fail()) {
                                    throw runtime_error("Input harus angka");
                                }
                                
                                addressHistory p = H.top;
                                int count = 1;
                                while (p != nullptr && count < no) {
                                    p = p->next;
                                    count++;
                                }
                                
                                if (p != nullptr) {
                                    cp.info = p->info;
                                    cp.isPlaying = true;
                                    cp.fromPlaylist = false;
                                    cp.currentPlaylistelm = nullptr;
                                    cout << "\nSekarang memutar: " << p->info.judul << " - " << p->info.artis << endl;
                                } else {
                                    cout << "Nomor tidak valid." << endl;
                                }
                            } else {
                                cout << "Riwayat kosong." << endl;
                            }
                        }
                    } catch (exception &e) {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        pilihanHistory = -1;
                    }
                } while (pilihanHistory != 0);
            } else if (pilihan == 9) {
                int pilihanArtist;
                do {
                    cout << "\n=== BROWSE BY ARTIS ===" << endl;
                    cout << "1. Lihat Semua Artis" << endl;
                    cout << "2. Lihat Album Artis" << endl;
                    cout << "3. Lihat Lagu di Album" << endl;
                    cout << "0. Kembali" << endl;
                    cout << "Pilihan: ";
                    
                    try {
                        cin >> pilihanArtist;
                        if (cin.fail()) {
                            throw runtime_error("Input tidak valid");
                        }
                        cin.ignore();
                        
                        if (pilihanArtist == 1) {
                            showAllArtists(AL);
                        } else if (pilihanArtist == 2) {
                            string namaArtis;
                            cout << "Nama artis: ";
                            getline(cin, namaArtis);
                            showArtistAlbums(AL, namaArtis);
                        } else if (pilihanArtist == 3) {
                            string namaArtis, namaAlbum;
                            cout << "Nama artis: ";
                            getline(cin, namaArtis);
                            cout << "Nama album: ";
                            getline(cin, namaAlbum);
                            showAlbumSongs(AL, namaArtis, namaAlbum);
                        }
                    } catch (exception &e) {
                        cout << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                        pilihanArtist = -1;
                    }
                } while (pilihanArtist != 0);
            } else if (pilihan == 10) {
                showAllSongs(L);
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }
    } while (pilihan != 0);
}

int main() {
    Library library;
    Playlist playlists[10];
    int playlistCount = 0;
    CurrentPlay currentPlay;
    PlayQueue playQueue;
    History history;
    ArtistList artistList;
    
    currentPlay.isPlaying = false;
    currentPlay.fromPlaylist = false;
    currentPlay.currentPlaylistelm = nullptr;
    
    createLibrary(library);
    createQueue(playQueue);
    createHistory(history);
    createArtistList(artistList);
    
    int pilihan;
    do {
        cout << "\n==================================" << endl;
        cout << "    APLIKASI PEMUTAR MUSIK" << endl;
        cout << "         musikinAza" << endl;
        cout << "==================================" << endl;
        cout << "1. Menu Admin" << endl;
        cout << "2. Menu User" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        
        try {
            cin >> pilihan;
            if (cin.fail()) {
                throw runtime_error("Input tidak valid");
            }
            
            if (pilihan == 1) {
                menuAdmin(library, playlists, playlistCount, artistList);
            } else if (pilihan == 2) {
                menuUser(library, playlists, playlistCount, currentPlay, playQueue, history, artistList);
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            pilihan = -1;
        }
    } while (pilihan != 0);
    
    cout << "\nTerima kasih telah menggunakan musikinAza!" << endl;
    return 0;
}
