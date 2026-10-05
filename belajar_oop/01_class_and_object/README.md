# Materi 01: Class and Object

## 1. Konsep Dasar

Dalam pemrograman berorientasi objek (OOP), Class dan Object adalah fondasi utama:

- **Class**: Cetak biru (blueprint) atau template tipe data buatan pengguna. Class mendefinisikan apa saja atribut (variabel/data) dan perilaku/fungsi (method) yang akan dimiliki oleh suatu entitas. Class belum memakan alokasi memori fisik untuk data saat baru didefinisikan.
- **Object**: Wujud nyata (instance) dari sebuah class. Ketika sebuah objek dibuat, sistem mengalokasikan ruang memori di RAM untuk menyimpan atribut-atribut dari objek tersebut.

## 2. Struktur Class di C++

Secara umum, class dideklarasikan dengan kata kunci `class` dan diakhiri dengan titik koma (`;`).

```cpp
class NamaClass {
public:
    // Atribut (Variabel)
    tipe_data namaVariabel;

    // Method (Fungsi Anggota)
    void namaFungsi() {
        // kode logika
    }
};
```

### Access Specifiers
C++ menyediakan 3 penentu hak akses:
- `public`: Anggota dapat diakses secara langsung dari mana saja di luar class.
- `private`: Anggota hanya bisa diakses dari dalam internal class itu sendiri (default untuk class di C++).
- `protected`: Anggota dapat diakses oleh internal class dan class turunannya (inheritance).

## 3. Penjelasan Alur Program main.cpp

1. **Definisi Class `Robot`**:
   - Memiliki atribut `name` (string) dan `batteryLevel` (integer).
   - Memiliki method `displayInfo()` untuk mencetak status robot ke layar.
   - Memiliki method `charge(int amount)` untuk menambah daya baterai hingga maksimal 100%.

2. **Instansiasi Objek di `main()`**:
   - `Robot robot1;` dan `Robot robot2;` dibuat di memori stack.
   - Setiap objek memiliki ruang memori terpisah, sehingga perubahan pada `robot2.batteryLevel` tidak akan memengaruhi `robot1.batteryLevel`.

3. **Pemanggilan Method**:
   - `robot1.displayInfo();` memanggil fungsi menggunakan konteks data milik `robot1`.
   - `robot2.charge(30);` menambah baterai khusus untuk `robot2`.

## 4. Cara Kompilasi dan Eksekusi

Jalankan perintah berikut di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Robot: Ichiro-01 | Baterai: 80%
Robot: Ichiro-02 | Baterai: 45%
Ichiro-02 sedang di-charge. Sisa: 75%
Robot: Ichiro-02 | Baterai: 75%
```
