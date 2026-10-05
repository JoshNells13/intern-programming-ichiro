# Materi 01: Class and Object

## 1. Konsep Inti

Bayangin pas lagi ngerancang robot:

- **Class**: Ini gambar cetak biru (blueprint) atau denah rancangannya. Di dalam blueprint ini, ditentuin data apa aja yang dimiliki robot (misal nama dan persentase baterai) serta aksi/method apa aja yang bisa dilakuin (misal nampilin status atau nge-charge baterai).
- **Object**: Ini wujud fisik aslinya pas udah diproduksi dan dinyalain di memori. Kalo bikin 2 objek robot dari satu class yang sama, mereka berdua itu independen dan punya data baterai masing-masing.

---

## 2. Struktur Dasar Penulisan

Di C++, struktur deklarasi class simpelnya kayak gini:

```cpp
class Robot {
public: // Bagian ini bisa diakses bebas dari luar (misal dari fungsi main)
    std::string name;
    int batteryLevel;

    void displayInfo() {
        // kode aksi di sini
    }
}; // Jangan lupa titik koma di ujung kurung kurawal
```

---

## 3. Bedah Alur File main.cpp

Alur eksekusi kodenya:

1. **Bikin Objek Robot 1 & 2**: Di fungsi `main()`, deklarasi `Robot robot1;` dan `Robot robot2;`. Sistem langsung alokasiin dua blok memori terpisah.
2. **Assign Data**: Isi nama `"Ichiro-01"` ke `robot1` dan `"Ichiro-02"` ke `robot2`.
3. **Cek Status**: Panggil `robot1.displayInfo()`, output bakal nampilin info milik `robot1`.
4. **Charge Baterai**: Panggil `robot2.charge(30)`. Fungsi ini nambahin baterai `robot2` tanpa ganggu baterai `robot1` sama sekali.

---

## 4. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Robot: Ichiro-01 | Baterai: 80%
Robot: Ichiro-02 | Baterai: 45%
Ichiro-02 sedang di-charge. Sisa: 75%
Robot: Ichiro-02 | Baterai: 75%
```
