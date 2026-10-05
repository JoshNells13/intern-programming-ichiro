# Materi 04: Inheritance (Pewarisan)

## 1. Konsep Inti

Inheritance (Pewarisan) itu cara bikin class baru (child class) yang otomatis mewarisi semua variabel dan method dari class yang udah ada (parent class).

### Keuntungan Utama:
- **Hemat Baris Kode (DRY)**: Ga perlu nulis ulang atribut umum kayak `name` dan `battery` di tiap jenis robot.
- **Hierarki Jelas & Rapi**: Parent class (`Robot`) megang data dasar umum, sedangkan child class (`StrikerRobot`, `GoalkeeperRobot`) tinggal nambahin jurus/fitur unik masing-masing.

---

## 2. Hak Akses: protected

Kalo child class butuh izin buat baca/ubah variabel milik parent class, tapi variabel itu tetep harus dikunci rapat dari akses liar di luar (misal dari `main()`), pake keyword `protected:`:

- `public`: Bebas diakses dari mana aja.
- `protected`: Cuma bisa diakses oleh parent class dan child class turunannya.
- `private`: Eksklusif cuma bisa diakses oleh class itu sendiri.

---

## 3. Bedah Alur File main.cpp

1. Parent class `Robot` nentuin variabel `name`, `battery`, dan method `status()`.
2. Class `StrikerRobot` mewarisi `Robot` dan nambahin skill nendang `kickBall()`.
3. Class `GoalkeeperRobot` mewarisi `Robot` dan nambahin skill diving `diveToSave()`.
4. Di `main()`, objek `striker` langsung bisa manggil `striker.status()` (fungsi warisan dari induk) dan `striker.kickBall()` (fungsi unik miliknya sendiri).

---

## 4. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Robot: Ichiro-Striker | Baterai: 90%
Ichiro-Striker menendang bola dengan kekuatan 250 N!

Robot: Ichiro-Keeper | Baterai: 95%
Ichiro-Keeper menangkap bola dengan reaksi 120 ms!
```
