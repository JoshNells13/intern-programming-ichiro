# Materi 02: Constructor and Destructor

## 1. Konsep Dasar

Dalam C++, lifecycle (daur hidup) sebuah objek dikendalikan oleh fungsi khusus bernama Constructor dan Destructor:

- **Constructor**: Fungsi khusus dengan nama yang sama persis dengan nama class dan tidak memiliki return value. Constructor dipanggil secara otomatis tepat saat objek dibuat untuk menginisialisasi atribut atau menyiapkan resource awal.
- **Destructor**: Fungsi khusus yang diawali tanda tilde (`~`) diikuti nama class (`~ClassName()`). Destructor dipanggil secara otomatis saat masa hidup objek selesai (objek keluar dari scope atau dihapus dengan `delete`) untuk membebaskan alokasi memori atau menutup resource.

## 2. Jenis-Jenis Constructor

### A. Default Constructor
Constructor yang tidak menerima parameter atau semua parameternya memiliki default value.
```cpp
Robot() : name("Unknown"), id(0) {}
```

### B. Parameterized Constructor
Constructor yang menerima argumen untuk menginisialisasi atribut dengan nilai spesifik saat objek dibuat.
```cpp
Robot(std::string rName, int rId) : name(rName), id(rId) {}
```

### C. Copy Constructor
Constructor yang digunakan untuk membuat objek baru sebagai salinan dari objek yang sudah ada dengan tipe yang sama.
```cpp
Robot(const Robot& other) : name(other.name + "_Clone"), id(other.id + 100) {}
```

### Member Initializer List
Sintaks `: name(rName), id(rId)` disebut *Member Initializer List*. Teknik ini lebih cepat dan efisien daripada melakukan assignment di dalam tubuh kurung `{ name = rName; id = rId; }` karena atribut diinisialisasi langsung saat dialokasikan.

## 3. Penjelasan Alur Program main.cpp

1. **Pembuatan `r1`**: Memanggil Default Constructor karena tanpa parameter.
2. **Pembuatan `r2`**: Memanggil Parameterized Constructor dengan nama `"Ichiro-Striker"` dan ID `7`.
3. **Pembuatan `r3 = r2`**: Memanggil Copy Constructor, menghasilkan robot baru dengan nama `"Ichiro-Striker_Clone"` dan ID `107`.
4. **Scope Blok `{ ... }`**:
   - `rTemp` dibuat di dalam blok scope terbatas.
   - Saat alur program melewati tanda kurung kurawal penutup `}`, `rTemp` langsung dihancurkan dan memicu pemanggilan Destructor `~Robot()` miliknya terlebih dahulu.
5. **Akhir `main()`**:
   - Objek `r3`, `r2`, dan `r1` dihancurkan secara berurutan dengan urutan terbalik dari pembuatannya (LIFO - Last In, First Out).

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
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
