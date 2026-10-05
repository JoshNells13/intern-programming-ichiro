# Materi 09: Memisahkan Class ke Banyak File (Multi-File Project)

## 1. Kenapa Mesti Dipecah Banyak File?

Di proyek real-world berskala menengah sampai gede, nulis semua class numpuk di satu file `main.cpp` bakal bikin kacau:
- File jadi kepanjangan dan ribet dinavigasi.
- Gampang bentrok nama fungsi/variabel (*naming collision*) dan rawan duplikasi kode.
- Waktu kompilasi lambat parah karena ubah dikit aja harus re-compile semua baris dari awal.

Standar industri di C++ memisahkan setiap class jadi 2 jenis file:
1. **Header File (`.hpp` atau `.h`)**: Isinya deklarasi antarmuka class (nama class, variabel, dan prototype method). File ini jadi "kontrak" yang di-include file lain.
2. **Source File (`.cpp`)**: Isinya implementasi logika detail dari tiap method yang udah dideklarasikan di header.

---

## 2. Struktur Folder & File

```text
09_separate_files/
├── Robot.hpp          <- Deklarasi Base Class Robot
├── Robot.cpp          <- Implementasi Base Class Robot
├── StrikerRobot.hpp   <- Deklarasi Derived Class StrikerRobot
├── StrikerRobot.cpp   <- Implementasi Derived Class StrikerRobot
├── main.cpp           <- Entry point program
└── README.md          <- Catatan materi
```

---

## 3. Konsep Penting

### A. Include Guards (`#ifndef`, `#define`, `#endif`)
Biar ga terjadi eror pendefinisian class ganda kalo satu file header di-include beberapa kali oleh file berbeda, selalu pasang include guard (atau `#pragma once`):

```cpp
#ifndef ROBOT_HPP
#define ROBOT_HPP

// Deklarasi class di sini

#endif
```

### B. Scope Resolution Operator (`::`)
Di file `.cpp`, pake tanda `NamaClass::` buat negasin kalo fungsi itu adalah implementasi milik method class yang bersangkutan:

```cpp
#include "Robot.hpp"

// Implementasi fungsi displayInfo milik class Robot
void Robot::displayInfo() const {
    // Logika method di sini
}
```

### C. Bedanya Include `""` vs `<>`
- `#include <iostream>`: Buat header library bawaan compiler / standar C++.
- `#include "Robot.hpp"`: Buat file header lokal buatan sendiri di dalam folder project.

---

## 4. Bedah Alur File main.cpp

1. `main.cpp` cuma perlu include file header doang: `#include "Robot.hpp"` dan `#include "StrikerRobot.hpp"`.
2. Bikin objek `baseBot` dan `strikerBot`, lalu jalanin fungsi masing-masing.
3. Objek dimasukin ke `std::vector<std::unique_ptr<Robot>>` buat ngebuktiin kalo *Runtime Polymorphism* tetep jalan mulus walau class-nya dipisah ke file yang berbeda.

---

## 5. Cara Compile Multi-File & Output

Kalo program dipecah jadi banyak file `.cpp`, compiler harus dikasih tau semua list file `.cpp`-nya biar linker bisa nyambungin deklarasi sama implementasinya.

### Perintah Compile GCC / G++:

```bash
# Opsi 1: Tulis satu-satu semua file .cpp
g++ -std=c++17 main.cpp Robot.cpp StrikerRobot.cpp -o main.exe
./main.exe

# Opsi 2: Pake wildcard (*.cpp) biar praktis
g++ -std=c++17 *.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
[Robot] Nama: Ichiro-Base | Baterai: 75%
Ichiro-Base di-charge +15% | Sisa: 90%

[StrikerRobot] Nama: Ichiro-Striker | Baterai: 90% | Kick Power: 300 N
Ichiro-Striker menendang bola dengan kekuatan 300 N!

--- Uji Polimorfisme Multi-File ---
[Robot] Nama: Ichiro-Observer | Baterai: 50%
[StrikerRobot] Nama: Ichiro-Forward | Baterai: 85% | Kick Power: 275 N
```
