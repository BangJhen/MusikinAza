Saya akan menjelaskan setiap fitur dalam aplikasi **musikinAza** secara mendetail berdasarkan struktur kode yang ada.

# Penjelasan Fitur Aplikasi musikinAza

## 1. **Struktur Data Utama**

### **Library (Double Linked List)**
- **Struktur**: Double linked list untuk menyimpan semua lagu
- **Cara Kerja**: Setiap node memiliki pointer `next` dan `prev`, memungkinkan traversal dua arah
- **Kegunaan**: Menyimpan database lagu utama dengan kemampuan insert, delete, update, dan search

### **Playlist (Single Linked List)**
- **Struktur**: Single linked list untuk menyimpan lagu dalam playlist
- **Cara Kerja**: Setiap node hanya memiliki pointer `next`, traversal satu arah
- **Kegunaan**: User bisa membuat maksimal 10 playlist berbeda

### **Queue (Antrian Pemutaran)**
- **Struktur**: Queue menggunakan linked list dengan FIFO (First In First Out)
- **Cara Kerja**: Lagu ditambahkan di `tail`, diambil dari `head`
- **Kegunaan**: Mengatur antrian lagu yang akan diputar

### **History (Stack)**
- **Struktur**: Stack menggunakan linked list dengan LIFO (Last In First Out)
- **Cara Kerja**: Lagu yang baru diputar di-push ke `top`, menampilkan maksimal 10 lagu terakhir
- **Kegunaan**: Menyimpan riwayat pemutaran lagu

### **Artist List (Multi-Level Linked List)**
- **Struktur**: Linked list bertingkat (Artist → Album → Songs)
- **Cara Kerja**: 
  - Level 1: List artis
  - Level 2: List album per artis
  - Level 3: List lagu per album
- **Kegunaan**: Browse lagu berdasarkan artis dan album

---

## 2. **Fitur Menu Admin**

### **A. Tambah Lagu ([addSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:28:0-40:1))**
**Cara Kerja:**
1. Input data lagu (ID, judul, artis, album, genre, tahun)
2. Alokasi node baru dengan [allocateLibrary](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:13:0-19:1)
3. Jika library kosong: node jadi head dan tail
4. Jika tidak kosong: tambahkan di akhir (tail)
5. Update pointer `prev` dan `next`
6. Otomatis menambahkan ke `ArtistList` dengan [addSongToArtist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:528:0-579:1)

**Detail [addSongToArtist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:528:0-579:1):**
- Cari artis, jika tidak ada buat node artis baru
- Cari album dalam artis, jika tidak ada buat node album baru
- Tambahkan lagu ke awal list lagu dalam album

### **B. Lihat Semua Lagu ([showAllSongs](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:42:0-59:1))**
**Cara Kerja:**
1. Cek apakah library kosong
2. Jika tidak kosong, traverse dari head ke tail
3. Print semua informasi lagu (ID, judul, artis, album, genre, tahun)

### **C. Update Lagu ([updateSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:72:0-90:1))**
**Cara Kerja:**
1. Traverse library mencari lagu berdasarkan ID
2. Gunakan flag `found` untuk menghentikan pencarian
3. Jika ditemukan: update judul, artis, genre, tahun (ID tetap)
4. Otomatis update di semua playlist dengan [updateSongInPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:392:0-405:1)
5. Jika tidak ditemukan: tampilkan pesan error

### **D. Hapus Lagu ([deleteSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:91:0-129:1))**
**Cara Kerja:**
1. Traverse library mencari lagu berdasarkan ID
2. Jika ditemukan:
   - Update pointer `prev` dan `next` dari node sebelum/sesudah
   - Handle kasus khusus: node di head atau tail
   - Hapus lagu dari semua playlist dengan [deleteSongFromPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:407:0-434:1)
   - Dealokasi memori node
3. Jika tidak ditemukan: tampilkan pesan error

---

## 3. **Fitur Menu User**

### **A. Cari Lagu ([searchSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:133:0-218:1))**
**Cara Kerja:**
1. Pilih metode pencarian:
   - **By ID**: Exact match dengan ID
   - **By Judul**: Substring search (partial match)
   - **By Artis**: Substring search (partial match)
2. Traverse library dan cek kondisi sesuai pilihan
3. Tampilkan semua lagu yang cocok
4. Gunakan flag `found` untuk tracking hasil

### **B. Putar Lagu dari Library ([playSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:220:0-231:1))**
**Cara Kerja:**
1. Panggil [findSongById](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:61:0-72:1) untuk cari lagu (return `Song` dengan ID -1 jika tidak ada)
2. Jika ditemukan (ID != -1):
   - Set `CurrentPlay.info` dengan data lagu
   - Set `isPlaying = true`
   - Set `fromPlaylist = false`
   - Set `currentPlaylistelm = nullptr`
   - Push ke history dengan [pushHistory](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:490:0-495:1)
3. Jika tidak ditemukan: tampilkan error

### **C. Stop Lagu ([stopSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:233:0-240:1))**
**Cara Kerja:**
1. Cek apakah ada lagu yang sedang diputar
2. Jika ya: set `isPlaying = false` dan tampilkan pesan
3. Jika tidak: tampilkan pesan tidak ada lagu

### **D. Next Lagu ([nextSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:269:0-289:1))**
**Cara Kerja:**
1. Cek apakah ada lagu yang sedang diputar
2. **Jika dari playlist**:
   - Cek apakah ada lagu berikutnya (`currentPlaylistelm->next`)
   - Jika ada: pindah ke lagu berikutnya
   - Jika tidak: tampilkan "sudah di akhir playlist"
3. **Jika dari library**:
   - Panggil [findSimilarSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:242:0-267:1) untuk cari lagu mirip
   - Prioritas: artis sama → genre sama
   - Jika ada: putar lagu mirip
   - Push ke history

### **E. Prev Lagu ([prevSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:287:0-301:1))**
**Cara Kerja:**
1. Cek apakah ada lagu yang sedang diputar
2. **Jika dari playlist**: tampilkan pesan "fitur tidak tersedia" (karena single linked list)
3. **Jika dari library**:
   - Sama seperti next, cari lagu mirip dengan [findSimilarSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:242:0-267:1)
   - Push ke history

**Detail [findSimilarSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:242:0-267:1):**
- Traverse library, skip lagu yang sedang diputar
- Cari lagu dengan artis sama (prioritas pertama)
- Cari lagu dengan genre sama (prioritas kedua)
- Return `Song` dengan ID -1 jika tidak ada yang mirip

### **F. Kelola Playlist**

#### **F.1. Buat Playlist Baru ([createPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:7:0-11:1))**
**Cara Kerja:**
1. Cek jumlah playlist (maksimal 10)
2. Input nama playlist
3. Inisialisasi `head = nullptr`, `tail = nullptr`
4. Increment `playlistCount`

#### **F.2. Tambah Lagu ke Playlist ([addToPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:307:0-318:1))**
**Cara Kerja:**
1. Pilih playlist dari daftar
2. Input ID lagu
3. Cari lagu di library dengan [findSongById](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:61:0-72:1)
4. Jika ditemukan:
   - Alokasi node baru dengan [allocatePlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:21:0-26:1)
   - Jika playlist kosong: node jadi head dan tail
   - Jika tidak: tambahkan di akhir (tail)

#### **F.3. Hapus Lagu dari Playlist ([removeFromPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:320:0-353:1))**
**Cara Kerja:**
1. Pilih playlist
2. Input ID lagu yang akan dihapus
3. Traverse playlist mencari lagu
4. Jika ditemukan:
   - Update pointer `next` dari node sebelumnya
   - Handle kasus khusus: node di head atau tail
   - Dealokasi memori
5. Gunakan flag `found` untuk menghentikan pencarian

#### **F.4. Lihat Playlist ([showPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:352:0-368:1))**
**Cara Kerja:**
1. Pilih playlist
2. Cek apakah playlist kosong
3. Traverse dan tampilkan semua lagu dalam playlist

#### **F.5. Putar dari Playlist ([playFromPlaylist](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:373:0-390:1))**
**Cara Kerja:**
1. Pilih playlist
2. Input ID lagu
3. Traverse playlist mencari lagu
4. Jika ditemukan:
   - Set `CurrentPlay` dengan data lagu
   - Set `fromPlaylist = true`
   - Set `currentPlaylistelm` ke node lagu tersebut
   - Push ke history

### **G. Antrian Pemutaran (Queue)**

#### **G.1. Tambah ke Antrian ([enqueueSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:441:0-454:1))**
**Cara Kerja:**
1. Input ID lagu
2. Cari lagu dengan [findSongById](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:61:0-72:1)
3. Jika ditemukan:
   - Alokasi node baru
   - Tambahkan di tail queue (FIFO)
   - Update pointer tail

#### **G.2. Lihat Antrian ([showQueue](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:468:0-480:1))**
**Cara Kerja:**
1. Cek apakah queue kosong
2. Traverse dari head ke tail
3. Tampilkan nomor urut dan info lagu

#### **G.3. Putar dari Antrian ([dequeueSong](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:456:0-466:1))**
**Cara Kerja:**
1. Cek apakah queue kosong
2. Ambil lagu dari head (FIFO)
3. Update head ke node berikutnya
4. Dealokasi node yang diambil
5. Set `CurrentPlay` dengan lagu tersebut
6. Push ke history

### **H. Riwayat Pemutaran (History)**

#### **H.1. Lihat Riwayat ([showHistory](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:502:0-514:1))**
**Cara Kerja:**
1. Cek apakah history kosong
2. Traverse dari top (maksimal 10 lagu)
3. Tampilkan nomor urut dan info lagu
4. LIFO: lagu terakhir diputar muncul pertama

#### **H.2. Putar dari Riwayat**
**Cara Kerja:**
1. Tampilkan history
2. Input nomor lagu
3. Traverse ke node ke-n dari top
4. Set `CurrentPlay` dengan lagu tersebut

**Detail [pushHistory](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:490:0-495:1):**
- Alokasi node baru
- Set `next` ke `top` saat ini
- Update `top` ke node baru (LIFO)

### **I. Browse by Artis**

#### **I.1. Lihat Semua Artis ([showAllArtists](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:577:0-588:1))**
**Cara Kerja:**
1. Cek apakah ada artis
2. Traverse list artis
3. Tampilkan nama semua artis

#### **I.2. Lihat Album Artis ([showArtistAlbums](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:594:0-613:1))**
**Cara Kerja:**
1. Input nama artis
2. Traverse list artis mencari artis tersebut
3. Jika ditemukan:
   - Traverse list album dalam artis
   - Tampilkan nama semua album

#### **I.3. Lihat Lagu di Album ([showAlbumSongs](cci:1://file:///Users/bangjhener/Desktop/Telkom/Semester%203/Struktur%20Data/Tugas/TUBES/musikinAza/musikinAza/musikinAza.cpp:611:0-639:1))**
**Cara Kerja:**
1. Input nama artis dan album
2. Traverse list artis mencari artis
3. Traverse list album mencari album
4. Jika ditemukan:
   - Traverse list lagu dalam album
   - Tampilkan ID dan judul lagu

---

## 4. **Fitur Khusus**

### **A. Sentinel Value (ID -1)**
- Digunakan untuk function yang return `Song` tanpa pointer
- ID -1 menandakan "lagu tidak ditemukan"
- Menghindari penggunaan pointer dan `nullptr`

### **B. Error Handling**
- Try-catch untuk input validation
- Cek `cin.fail()` untuk input non-numerik
- Clear buffer dengan `cin.clear()` dan `cin.ignore()`

### **C. Sinkronisasi Data**
- Update lagu di library otomatis update di semua playlist
- Hapus lagu di library otomatis hapus di semua playlist
- Tambah lagu otomatis masuk ke ArtistList

---

Aplikasi ini mengimplementasikan berbagai struktur data (double linked list, single linked list, queue, stack, multi-level linked list) dengan prinsip **tidak menggunakan `return;` dan `break`** pada function void, menggunakan flag boolean dan struktur if-else untuk kontrol alur.