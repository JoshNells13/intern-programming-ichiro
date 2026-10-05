# Materi 05: Polymorphism (Polimorfisme)

## 1. Konsep Dasar

Polymorphism (dari bahasa Yunani: "banyak bentuk") memungkinkan antarmuka yang sama diperlakukan secara seragam, namun menghasilkan perilaku berbeda sesuai tipe objek konkret saat runtime.

Dalam C++, polimorfisme terbagi menjadi dua:
1. **Compile-Time Polymorphism (Static Binding)**: Function Overloading dan Operator Overloading.
2. **Runtime Polymorphism (Dynamic Binding)**: Virtual Functions yang dipanggil melalui pointer atau reference base class.

## 2. Kata Kunci Utama

- **`virtual`**: Ditulis pada deklarasi fungsi di base class untuk mengaktifkan Dynamic Dispatch via vtable (Virtual Method Table).
- **`override`**: Ditulis pada child class untuk memastikan method tersebut benar-benar menimpa (override) fungsi virtual dari base class. Jika ada salah ketik nama atau tipe parameter, compiler akan langsung memberi tahu error.
- **`virtual ~BaseClass() = default;`**: Wajib didefinisikan pada base class agar ketika objek child dihapus melalui pointer base (`delete basePtr`), destructor milik child class juga ikut dipanggil (menghindari memory leak).

## 3. Penjelasan Alur Program main.cpp

1. Base class `Robot` mendefinisikan method `virtual void performAction() const`.
2. Tiga class turunan (`StrikerRobot`, `DefenderRobot`, `RefereeRobot`) masing-masing meng-override `performAction()`.
3. Di dalam `main()`, sebuah vektor smart pointer `std::vector<std::unique_ptr<Robot>>` menampung ketiga tipe robot tersebut dalam wadah bertipe seragam (`Robot*`).
4. Saat iterasi `member->performAction()` dieksekusi, C++ secara otomatis mendeteksi tipe objek asli di memori dan memanggil method yang sesuai untuk masing-masing robot.

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Striker berlari dan menembak ke gawang musuh!
Defender memblokir pergerakan lawan!
Referee meniup peluit tanda pelanggaran!
```
