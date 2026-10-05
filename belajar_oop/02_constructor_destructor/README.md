# Materi 02: Constructor and Destructor

## 1. Konsep Inti

Setiap objek di C++ punya siklus hidup (lahir -> dipake -> musnah):

- **Constructor**: Fungsi khusus yang auto-dieksekusi pas objek "lahir" (dibuat). Fungsinya buat ngasih nilai inisialisasi awal ke variabel biar memorinya ga nyimpen nilai sampah/acak.
- **Destructor**: Fungsi khusus yang auto-dieksekusi pas objek "mati" (keluar dari scope kurung kurawal atau didelete). Fungsinya buat beres-beres resource memori biar ga kena memory leak.

---

## 2. Tiga Jenis Constructor Utama

1. **Default Constructor**: Dipanggil pas bikin objek polosan tanpa ngasih argumen (`Robot r1;`).
2. **Parameterized Constructor**: Dipanggil pas ngirim argumen nilai awal spesifik (`Robot r2("Ichiro-Striker", 7);`).
3. **Copy Constructor**: Dipanggil pas cloning/duplikasi objek yang udah ada (`Robot r3 = r2;`).

### Best Practice: Member Initializer List
Di C++, inisialisasi variabel constructor paling rapi dan cepet itu pake format titik dua (`:`) sebelum isi kurung kurawal:
```cpp
Robot(std::string rName, int rId) : name(rName), id(rId) {
    // Tubuh constructor
}
```
Cara ini lebih optimal daripada assignment manual di dalam body `{ name = rName; }`.

---

## 3. Bedah Alur File main.cpp

1. Bikin 3 objek di awal: `r1` (default), `r2` (berparameter), dan `r3` (copy constructor dari `r2`).
2. Masuk ke blok scope lokal `{ ... }`, bikin objek sementara `rTemp`.
3. Pas program ngelewatin kurung kurawal penutup `}`, `rTemp` langsung dimusnahin dan memicu Destructor `~Robot()` duluan.
4. Di akhir fungsi `main()`, objek `r3`, `r2`, dan `r1` bakal dihancurin otomatis dengan urutan LIFO (Last-In First-Out / kebalikan dari urutan dibuat).

---

## 4. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
=== Scope Awal ===
[Constructor Default] Robot baru dibuat!
[Constructor Param] Robot Ichiro-Striker (ID: 7) dibuat!
[Copy Constructor] Clone dari Ichiro-Striker dibuat!
-> Info: Unknown [ID: 0]
-> Info: Ichiro-Striker [ID: 7]
-> Info: Ichiro-Striker_Clone [ID: 107]

--- Masuk Inner Scope ---
[Constructor Param] Robot TempBot (ID: 99) dibuat!
-> Info: TempBot [ID: 99]
--- Keluar Inner Scope ---
[Destructor] Robot TempBot dihapus dari memori.

=== Scope Akhir ===
[Destructor] Robot Ichiro-Striker_Clone dihapus dari memori.
[Destructor] Robot Ichiro-Striker dihapus dari memori.
[Destructor] Robot Unknown dihapus dari memori.
```
