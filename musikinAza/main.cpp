#include <iostream>
#include "musikinAza.h"

using namespace std;

void menuAdmin(Library &L, Playlist playlists[], int &playlistCount) {
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
                cout << "Masukkan Genre: ";
                getline(cin, s.genre);
                cout << "Masukkan Tahun: ";
                cin >> s.tahun;
                if (cin.fail()) {
                    throw runtime_error("Tahun harus angka");
                }
                addSong(L, s);
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

void menuUser(Library &L, Playlist playlists[], int &playlistCount, CurrentPlay &cp) {
    int pilihan;
    do {
        cout << "\n=== MENU USER ===" << endl;
        cout << "1. Cari Lagu" << endl;
        cout << "2. Putar Lagu dari Library" << endl;
        cout << "3. Stop Lagu" << endl;
        cout << "4. Next Lagu" << endl;
        cout << "5. Prev Lagu" << endl;
        cout << "6. Kelola Playlist" << endl;
        cout << "7. Lihat Semua Lagu" << endl;
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
            } else if (pilihan == 3) {
                stopSong(cp);
            } else if (pilihan == 4) {
                nextSong(L, cp);
            } else if (pilihan == 5) {
                prevSong(L, cp);
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
    currentPlay.isPlaying = false;
    currentPlay.fromPlaylist = false;
    currentPlay.currentPlaylistNode = nullptr;
    
    createLibrary(library);
    
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
                menuAdmin(library, playlists, playlistCount);
            } else if (pilihan == 2) {
                menuUser(library, playlists, playlistCount, currentPlay);
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
