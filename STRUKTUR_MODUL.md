# Dokumentasi Struktur Modular musikinAza

## Arsitektur Modular

Aplikasi musikinAza menggunakan arsitektur modular dengan pemisahan header berdasarkan struktur data dan fungsionalitas.

## Hierarki Modul

```
musikinAza.h (Main Header)
├── song.h (Base)
├── library.h (depends on: song.h)
├── playlist.h (depends on: song.h)
├── player.h (depends on: library.h, playlist.h)
├── queue.h (depends on: song.h)
├── history.h (depends on: song.h)
└── artist.h (depends on: song.h, library.h)
```

## Detail Modul

### 1. song.h
**Tipe**: Base Module
**Struktur Data**: Record/Struct
**Deskripsi**: Definisi struct Song sebagai unit data dasar

```cpp
struct Song {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
    string album;
};
```

### 2. library.h
**Tipe**: Data Structure Module
**Struktur Data**: Doubly Linked List
**Deskripsi**: Manajemen library lagu dengan navigasi dua arah

**Typedef**:
- `typedef struct elmLibrary* addressLibrary;`

**Struct**:
- `elmLibrary`: Node dengan pointer next dan prev
- `Library`: Head dan tail pointer

**Fungsi**:
- `createLibrary()`: Inisialisasi library
- `allocateLibrary()`: Alokasi node baru
- `addSong()`: Tambah lagu ke library
- `showAllSongs()`: Tampilkan semua lagu
- `findSongById()`: Cari lagu berdasarkan ID
- `updateSong()`: Update data lagu
- `deleteSong()`: Hapus lagu dari library
- `searchSong()`: Cari lagu (ID/judul/artis)
- `findSimilarSong()`: Cari lagu mirip

### 3. playlist.h
**Tipe**: Data Structure Module
**Struktur Data**: Singly Linked List
**Deskripsi**: Manajemen playlist dengan urutan pemutaran

**Typedef**:
- `typedef struct elmPlaylist* addressPlaylist;`

**Struct**:
- `elmPlaylist`: Node dengan pointer next saja
- `Playlist`: Head, tail, dan nama playlist
- `CurrentPlay`: Status pemutaran saat ini

**Fungsi**:
- `createPlaylist()`: Inisialisasi playlist
- `allocatePlaylist()`: Alokasi node baru
- `addToPlaylist()`: Tambah lagu ke playlist
- `removeFromPlaylist()`: Hapus lagu dari playlist
- `showPlaylist()`: Tampilkan isi playlist
- `playFromPlaylist()`: Putar lagu dari playlist
- `updateSongInPlaylist()`: Update lagu di playlist
- `deleteSongFromPlaylist()`: Hapus lagu dari playlist

### 4. player.h
**Tipe**: Functional Module
**Deskripsi**: Fungsi-fungsi kontrol pemutaran

**Fungsi**:
- `playSong()`: Putar lagu dari library
- `stopSong()`: Hentikan pemutaran
- `nextSong()`: Lagu berikutnya
- `prevSong()`: Lagu sebelumnya

### 5. queue.h
**Tipe**: Data Structure Module
**Struktur Data**: Queue (FIFO)
**Deskripsi**: Antrian pemutaran lagu

**Typedef**:
- `typedef struct elmQueue* addressQueue;`

**Struct**:
- `elmQueue`: Node queue
- `PlayQueue`: Head dan tail pointer

**Fungsi**:
- `createQueue()`: Inisialisasi queue
- `enqueueSong()`: Tambah lagu ke antrian
- `dequeueSong()`: Ambil lagu dari antrian
- `showQueue()`: Tampilkan antrian
- `isQueueEmpty()`: Cek apakah queue kosong

### 6. history.h
**Tipe**: Data Structure Module
**Struktur Data**: Stack (LIFO)
**Deskripsi**: Riwayat pemutaran lagu

**Typedef**:
- `typedef struct elmHistory* addressHistory;`

**Struct**:
- `elmHistory`: Node stack
- `History`: Top pointer

**Fungsi**:
- `createHistory()`: Inisialisasi history
- `pushHistory()`: Tambah lagu ke riwayat
- `popHistory()`: Ambil lagu dari riwayat
- `showHistory()`: Tampilkan riwayat
- `isHistoryEmpty()`: Cek apakah history kosong

### 7. artist.h
**Tipe**: Data Structure Module
**Struktur Data**: Multi Linked List (3 level)
**Deskripsi**: Organisasi hierarki Artis → Album → Lagu

**Typedef**:
- `typedef struct elmAlbum* addressAlbum;`
- `typedef struct elmArtist* addressArtist;`

**Struct**:
- `elmArtist`: Node artis dengan pointer ke albums
- `elmAlbum`: Node album dengan pointer ke songs
- `ArtistList`: Head pointer ke list artis

**Fungsi**:
- `createArtistList()`: Inisialisasi artist list
- `addSongToArtist()`: Tambah lagu ke struktur artis-album
- `showAllArtists()`: Tampilkan semua artis
- `showArtistAlbums()`: Tampilkan album per artis
- `showAlbumSongs()`: Tampilkan lagu per album

## Keuntungan Struktur Modular

1. **Separation of Concerns**: Setiap modul fokus pada satu tanggung jawab
2. **Reusability**: Modul dapat digunakan kembali di project lain
3. **Maintainability**: Mudah mencari dan memperbaiki bug
4. **Scalability**: Mudah menambah fitur baru tanpa mengubah modul lain
5. **Readability**: Kode lebih mudah dibaca dan dipahami
6. **Compilation**: Perubahan pada satu modul tidak memerlukan recompile semua file

## Dependency Graph

```
main.cpp
    └── musikinAza.h
            ├── song.h (no dependencies)
            ├── library.h → song.h
            ├── playlist.h → song.h
            ├── player.h → library.h, playlist.h
            ├── queue.h → song.h
            ├── history.h → song.h
            └── artist.h → song.h, library.h
```

## Cara Kompilasi

Karena menggunakan struktur modular, kompilasi tetap sederhana:

```bash
g++ -std=c++11 musikinAza/main.cpp musikinAza/musikinAza.cpp -o musikinAza
```

Compiler akan otomatis mengikuti include directives dan mengcompile semua dependencies.

## Best Practices

1. **Include Guards**: Semua header menggunakan `#ifndef` untuk mencegah multiple inclusion
2. **Forward Declaration**: Menggunakan `struct` keyword untuk forward declaration
3. **Typedef Consistency**: Semua pointer menggunakan typedef dengan format `address*`
4. **Naming Convention**: Struct menggunakan prefix `elm` (element) untuk node types
5. **Minimal Dependencies**: Setiap modul hanya include yang benar-benar dibutuhkan
