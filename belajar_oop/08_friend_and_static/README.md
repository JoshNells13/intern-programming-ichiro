# Materi 08: Static Members and Friend Concept

## 1. Static Members

Dalam C++, kata kunci `static` di dalam class digunakan untuk mendefinisikan anggota yang menjadi milik class secara global, bukan milik instansiasi objek individual.

### A. Static Member Variable
- Variabel ini dialokasikan hanya satu kali di memori dan dibagi (shared) oleh seluruh objek dari class tersebut.
- Harus didefinisikan/diinisialisasi sekali di luar deklarasi class (`int Joint::totalJoints = 0;`).

### B. Static Member Function
- Fungsi yang dapat dipanggil langsung menggunakan nama class tanpa perlu membuat objek (`Joint::getTotalJoints()`).
- Fungsi static hanya bisa mengakses variabel static dan fungsi static lainnya (tidak memiliki pointer `this`).

## 2. Konsep Friend (Friend Function & Friend Class)

Secara default, data `private` dan `protected` terisolasi rapat. Namun, terkadang dua class atau satu fungsi utilitas eksternal memerlukan akses langsung ke data privat demi efisiensi atau desain khusus.

- **Friend Function**: Fungsi non-member yang dideklarasikan dengan kata kunci `friend` di dalam suatu class. Fungsi ini berhak mengakses semua anggota privat class tersebut.
- **Friend Class**: Jika `class A` menyatakan `friend class B;`, maka seluruh method di dalam `class B` memiliki izin untuk mengakses anggota privat dari `class A`.

## 3. Penjelasan Alur Program main.cpp

1. `Joint::totalJoints` melacak berapa banyak objek `Joint` yang aktif di memori secara otomatis (bertambah saat constructor dieksekusi, berkurang saat destructor dieksekusi).
2. Fungsi `inspectJointPrivate(const Joint& j)` membaca atribut privat `jointName` dan `currentAngle` karena sudah diberi hak akses melalui `friend void inspectJointPrivate(...)`.
3. Class `Motor` dideklarasikan sebagai `friend class Motor;` di dalam `Joint`, sehingga method `applyTorque` milik `Motor` dapat langsung memanipulasi variabel privat `currentAngle` dari objek `Joint`.

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Jumlah awal joint: 0
Jumlah joint sekarang: 2

[Friend Function Inspection] Joint: Knee_Left | Angle: 45 deg
[Motor] Menggerakkan joint Knee_Left dengan torsi 15 Nm.
[Friend Function Inspection] Joint: Knee_Left | Angle: 46.5 deg
```
