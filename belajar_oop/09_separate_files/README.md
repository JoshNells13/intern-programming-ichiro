# Materi 09: Memisahkan Class ke Banyak File (Multi-File Project)

## 1. Mengapa Perlu Memecah File?

Dalam proyek profesional berskala menengah hingga besar, menulis seluruh class di dalam satu file `main.cpp` akan menimbulkan masalah:
- File menjadi sangat panjang dan sulit dinavigasi.
- Terjadi konflik nama (naming collision) dan duplikasi kode.
- Waktu kompilasi menjadi lambat karena perubahan kecil memicu kompilasi ulang seluruh kode program.

Standar industri C++ memisahkan kode menjadi 2 jenis file untuk setiap class:
1. **Header File (`.hpp` atau `.h`)**: Berisi deklarasi antarmuka class (nama class, atribut, dan prototype method). File ini menjadi "kontrak" yang di-include oleh file lain.
2. **Source File (`.cpp`)**: Berisi implementasi detail dari setiap method yang telah dideklarasikan di header file.

---

## 2. Struktur Folder & File

```text
09_separate_files/
├── Robot.hpp          <- Deklarasi Base Class Robot
├── Robot.cpp          <- Implementasi Base Class Robot
├── StrikerRobot.hpp   <- Deklarasi Derived Class StrikerRobot
├── StrikerRobot.cpp   <- Implementasi Derived Class StrikerRobot
├── main.cpp           <- Entry point program
└── README.md          <- Dokumentasi materi
```

---

## 3. Konsep Penting

### A. Include Guards (`#ifndef`, `#define`, `#endif`)
Untuk mencegah pendefinisian class ganda jika sebuah header di-include lebih dari satu kali oleh file yang berbeda, selalu gunakan include guard atau `#pragma once`:

```cpp
#ifndef ROBOT_HPP
#define ROBOT_HPP

// Deklarasi class di sini

#endif
```

### B. Scope Resolution Operator (`::`)
Pada file `.cpp`, gunakan operator `NamaClass::` untuk menunjukkan bahwa fungsi tersebut adalah implementasi dari method milik class tertentu:

```cpp
#include "Robot.hpp"

// Mengisi implementasi method displayInfo milik class Robot
void Robot::displayInfo() const {
    // Logika method
}
```

### C. Penggunaan Tanda Petik Ganda `""` vs Kurung Siku `<>`
- `#include <iostream>`: Untuk header standar bawaan compiler C++.
- `#include "Robot.hpp"`: Untuk header lokal buatan sendiri di dalam proyek.

---

## 4. Penjelasan Alur Program main.cpp

1. `main.cpp` hanya perlu menyertakan file header: `#include "Robot.hpp"` dan `#include "StrikerRobot.hpp"`.
2. Program membuat objek `baseBot` dan `strikerBot`, kemudian menjalankan fungsi masing-masing.
3. Objek dimasukkan ke dalam `std::vector<std::unique_ptr<Robot>>` untuk membuktikan bahwa Runtime Polymorphism tetap bekerja optimal meskipun class berada di file yang terpisah.

---

## 5. Cara Kompilasi Multi-File

Ketika sebuah program terdiri dari beberapa file `.cpp`, compiler harus mengikutsertakan seluruh file `.cpp` tersebut agar linker dapat menghubungkan deklarasi dengan implementasinya.

### Perintah Kompilasi GCC / G++:

```bash
# Opsi 1: Kompilasi seluruh file .cpp secara bersamaan
g++ -std=c++17 main.cpp Robot.cpp StrikerRobot.cpp -o main.exe
./main.exe

# Opsi 2: Menggunakan wildcard (*.cpp)
g++ -std=c++17 *.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
[Robot] Nama: Ichiro-Base | Baterai: 75%
Ichiro-Base di-charge +15% | Sisa: 90%

[StrikerRobot] Nama: Ichiro-Striker | Baterai: 90% | Kick Power: 300 N
Ichiro-Striker menendang bola dengan kekuatan 300 N!

--- Uji Polimorfisme Multi-File ---
[Robot] Nama: Ichiro-Observer | Baterai: 50%
[StrikerRobot] Nama: Ichiro-Forward | Baterai: 85% | Kick Power: 275 N
```
