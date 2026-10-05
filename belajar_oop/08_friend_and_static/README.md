# Materi 08: Static Members and Friend Concept

## 1. Static Members

Di C++, keyword `static` di dalem class dipake buat nentuin atribut atau method yang nempel ke class secara global, bukan nempel per masing-masing objek individual.

### A. Static Member Variable
- Variabel ini cuma dialokasiin 1 kali di memori dan di-share bareng-bareng sama semua instance objek dari class itu.
- Wajib didefinisiin/diinisialisasi sekali di luar deklarasi class (`int Joint::totalJoints = 0;`).

### B. Static Member Function
- Fungsi yang bisa langsung dipanggil via nama class tanpa harus repot bikin objeknya dulu (`Joint::getTotalJoints()`).
- Fungsi static cuma bisa akses variabel static dan fungsi static lainnya (ga punya pointer `this`).

---

## 2. Konsep Friend (Friend Function & Friend Class)

Normalnya data `private` dan `protected` terkunci rapat. Tapi ada kalanya fungsi helper atau class lain butuh akses langsung ke data privat demi performa dan desain khusus.

- **Friend Function**: Fungsi luar (non-member) yang dikasih tiket VIP pake keyword `friend` di dalem class. Fungsi ini bebas ngakses member private class itu.
- **Friend Class**: Kalo `class A` nulis `friend class B;`, maka semua fungsi di dalem `class B` punya akses bebas ke isi private milik `class A`.

---

## 3. Bedah Alur File main.cpp

1. `Joint::totalJoints` otomatis ngitung jumlah objek `Joint` yang aktif di memori (nambah pas constructor kepanggil, ngurang pas destructor kepanggil).
2. Fungsi `inspectJointPrivate(const Joint& j)` bisa baca variabel privat `jointName` dan `currentAngle` karena udah dapet izin VIP via `friend void inspectJointPrivate(...)`.
3. Class `Motor` dideklarasiin sebagai `friend class Motor;` di `Joint`, jadi method `applyTorque` milik `Motor` bisa langsung ngubah data privat `currentAngle` objek `Joint`.

---

## 4. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Jumlah awal joint: 0
Jumlah joint sekarang: 2

[Friend Function Inspection] Joint: Knee_Left | Angle: 45 deg
[Motor] Menggerakkan joint Knee_Left dengan torsi 15 Nm.
[Friend Function Inspection] Joint: Knee_Left | Angle: 46.5 deg
```
