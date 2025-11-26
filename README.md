# musikinAza

Aplikasi pemutar musik berbasis konsol yang dibangun menggunakan C++ dengan implementasi struktur data Doubly Linked List dan Singly Linked List.

## Deskripsi

musikinAza adalah aplikasi manajemen dan pemutaran musik yang memungkinkan admin mengelola library lagu dan user untuk memutar lagu serta membuat playlist. Aplikasi ini dibuat sebagai tugas besar mata kuliah Struktur Data.

## Struktur Data

- **Doubly Linked List**: Digunakan untuk menyimpan library lagu, memungkinkan navigasi maju-mundur
- **Singly Linked List**: Digunakan untuk menyimpan playlist, efisien untuk urutan pemutaran
- **Record (Struct)**: Menyimpan data lagu (ID, judul, artis, genre, tahun)

## Fitur

### Menu Admin
- Tambah lagu baru ke library
- Lihat semua lagu di library
- Update data lagu (otomatis update di semua playlist)
- Hapus lagu (otomatis terhapus dari semua playlist)

### Menu User
- Cari lagu berdasarkan ID, judul, atau artis
- Putar dan stop lagu
- Next/Prev lagu:
  - Di playlist: mengikuti urutan playlist
  - Di library: memutar lagu mirip (prioritas artis sama > genre sama)
- Kelola playlist:
  - Buat playlist baru
  - Tambah lagu ke playlist
  - Hapus lagu dari playlist
  - Lihat isi playlist
  - Putar lagu dari playlist

## Cara Kompilasi

### Menggunakan Terminal
```bash
g++ -std=c++11 musikinAza/main.cpp musikinAza/musikinAza.cpp -o musikinAza
./musikinAza
```

### Menggunakan Xcode
1. Buka project `musikinAza.xcodeproj`
2. Build and Run (Cmd + R)

## Cara Penggunaan

### 1. Menu Utama
Saat aplikasi dijalankan, akan muncul menu utama:
```
==================================
    APLIKASI PEMUTAR MUSIK
         musikinAza
==================================
1. Menu Admin
2. Menu User
0. Keluar
```

### 2. Menu Admin
Pilih opsi 1 untuk masuk ke menu admin:
- **Tambah Lagu**: Masukkan ID, judul, artis, genre, dan tahun
- **Lihat Semua Lagu**: Menampilkan seluruh lagu di library
- **Update Lagu**: Ubah data lagu berdasarkan ID
- **Hapus Lagu**: Hapus lagu dari library dan semua playlist

### 3. Menu User
Pilih opsi 2 untuk masuk ke menu user:
- **Cari Lagu**: Cari berdasarkan ID, judul, atau artis
- **Putar Lagu**: Masukkan ID lagu yang ingin diputar
- **Stop Lagu**: Hentikan lagu yang sedang diputar
- **Next/Prev**: Navigasi ke lagu berikutnya/sebelumnya
- **Kelola Playlist**: Buat dan atur playlist

### 4. Kelola Playlist
Di menu user, pilih "Kelola Playlist" untuk:
- Membuat playlist baru (maksimal 10 playlist)
- Menambah lagu dari library ke playlist
- Menghapus lagu dari playlist
- Melihat isi playlist
- Memutar lagu dari playlist

## Contoh Penggunaan

### Menambah Lagu (Admin)
```
Menu Admin > Tambah Lagu
Masukkan ID: 1
Masukkan Judul: Bohemian Rhapsody
Masukkan Artis: Queen
Masukkan Genre: Rock
Masukkan Tahun: 1975
```

### Membuat Playlist (User)
```
Menu User > Kelola Playlist > Buat Playlist Baru
Nama playlist: My Favorites
```

### Memutar Lagu (User)
```
Menu User > Putar Lagu dari Library
Masukkan ID lagu: 1
```

## Error Handling

Aplikasi dilengkapi dengan exception handling untuk validasi input:
- Input non-numerik pada field yang memerlukan angka
- ID lagu yang tidak ditemukan
- Playlist kosong atau tidak ada

## Ketentuan Khusus

1. **Update Lagu**: Jika admin mengupdate data lagu, perubahan otomatis berlaku di semua playlist
2. **Hapus Lagu**: Jika admin menghapus lagu, lagu tersebut otomatis terhapus dari semua playlist
3. **Lagu Mirip**: Algoritma mencari lagu mirip memprioritaskan artis yang sama, kemudian genre yang sama
4. **Next/Prev di Playlist**: Mengikuti urutan lagu di playlist
5. **Next/Prev di Library**: Memutar lagu yang mirip dengan lagu saat ini

## Struktur File

```
musikinAza/
├── musikinAza/
│   ├── main.cpp          # Program utama dan menu
│   ├── musikinAza.h      # Header file dengan deklarasi
│   └── musikinAza.cpp    # Implementasi fungsi
└── README.md
```

## Teknologi

- **Bahasa**: C++
- **Standard**: C++11
- **IDE**: Xcode (macOS)
- **Compiler**: g++ / clang++

## Catatan

- Aplikasi ini adalah program konsol, tidak memiliki GUI
- "Memutar lagu" ditampilkan sebagai notifikasi teks
- Data lagu tidak persisten (hilang saat aplikasi ditutup)
- Maksimal 10 playlist dapat dibuat
