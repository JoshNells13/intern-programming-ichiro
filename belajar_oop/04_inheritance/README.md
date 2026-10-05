# Materi 04: Inheritance (Pewarisan)

## 1. Konsep Dasar

Inheritance adalah pilar OOP yang memungkinkan suatu class (Child/Derived Class) mewarisi atribut dan method dari class lain (Parent/Base Class).

### Keuntungan Inheritance
- **Reusabilitas Kode (Code Reusability)**: Tidak perlu menulis ulang logika umum yang sama di banyak class.
- **Ekstensibilitas (Extensibility)**: Memudahkan penambahan fitur baru dengan memperluas class yang sudah ada.
- **Hierarki yang Jelas**: Membangun hubungan logis berbasis "is-a" (contoh: StrikerRobot *is a* Robot).

## 2. Tingkat Akses: protected

| Access Specifier | Akses dalam Class Sendiri | Akses di Child Class | Akses di Luar Class / main() |
| :--- | :---: | :---: | :---: |
| `public` | Ya | Ya | Ya |
| `protected` | Ya | Ya | Tidak |
| `private` | Ya | Tidak | Tidak |

Dengan menggunakan `protected`, variabel `name` dan `battery` milik class `Robot` dapat dibaca/diubah langsung oleh `StrikerRobot` tanpa harus menjadikannya `public` untuk umum.

## 3. Constructor Chaining

Ketika objek derived class dibuat:
1. Constructor base class dieksekusi terlebih dahulu untuk menyiapkan data dasar.
2. Constructor derived class dieksekusi setelahnya untuk menyiapkan data tambahannya.

```cpp
StrikerRobot(std::string rName, int rBattery, int power)
    : Robot(rName, rBattery), kickPower(power) {}
```

## 4. Penjelasan Alur Program main.cpp

1. Class `Robot` berfungsi sebagai parent class dengan method `status()`.
2. `StrikerRobot` mewarisi `Robot`, menambahkan atribut `kickPower` dan fungsi spesifik `kickBall()`.
3. `GoalkeeperRobot` mewarisi `Robot`, menambahkan atribut `saveReactionMs` dan fungsi `diveToSave()`.
4. Objek `striker` dapat langsung memanggil method warisan `striker.status()` sekaligus method khususnya `striker.kickBall()`.

## 5. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Robot: Ichiro-Striker | Baterai: 90%
Ichiro-Striker menendang bola dengan kekuatan 250 N!

Robot: Ichiro-Keeper | Baterai: 95%
Ichiro-Keeper menangkap bola dengan reaksi 120 ms!
```
