# Catatan Belajar OOP C++ (Personal Notes)

Ini rangkuman dan catatan pribadi gw buat nguasain konsep Object-Oriented Programming (OOP) di C++ secara bertahap, dari dasar banget sampai level lanjutan.

Semua materi sengaja dipecah ke folder terpisah biar belajarnya fokus satu topik per waktu.

---

## Peta Materi Belajar

| No | Materi | Inti yang Dibahas | File Kode |
| :---: | :--- | :--- | :--- |
| 01 | [01_class_and_object](./01_class_and_object/) | Bikin blueprint (Class) dan bentuk nyatanya (Object). | [main.cpp](./01_class_and_object/main.cpp) |
| 02 | [02_constructor_destructor](./02_constructor_destructor/) | Setup inisialisasi awal dan auto-clean memori pas objek musnah. | [main.cpp](./02_constructor_destructor/main.cpp) |
| 03 | [03_encapsulation](./03_encapsulation/) | Proteksi data biar ga asal diobrak-abrik dari luar (private, getter, setter). | [main.cpp](./03_encapsulation/main.cpp) |
| 04 | [04_inheritance](./04_inheritance/) | Warisin atribut & method dari parent class biar ga usah nulis ulang kode. | [main.cpp](./04_inheritance/main.cpp) |
| 05 | [05_polymorphism](./05_polymorphism/) | Satu pemanggilan fungsi, tapi perilakunya beda-beda tergantung objek aslinya. | [main.cpp](./05_polymorphism/main.cpp) |
| 06 | [06_abstraction](./06_abstraction/) | Bikin kontrak interface pakai abstract class & pure virtual function. | [main.cpp](./06_abstraction/main.cpp) |
| 07 | [07_operator_overloading](./07_operator_overloading/) | Bikin operator bawaan (+, ==, <<) paham cara proses objek buatan sendiri. | [main.cpp](./07_operator_overloading/main.cpp) |
| 08 | [08_friend_and_static](./08_friend_and_static/) | Variabel global per class (static) dan akses jalur VIP (friend). | [main.cpp](./08_friend_and_static/main.cpp) |
| 09 | [09_separate_files](./09_separate_files/) | Struktur modular standar industri: pisah file .hpp (header) & .cpp (source). | [main.cpp](./09_separate_files/main.cpp) |

---

## 4 Pilar Utama OOP yang Wajib Diinget

1. **Encapsulation**: Bungkus data rapat-rapat pake `private` biar ga gampang dirusak atau diubah sembarangan dari luar.
2. **Inheritance**: Turunin sifat parent class ke child class biar hemat baris kode dan DRY (Don't Repeat Yourself).
3. **Polymorphism**: Pasang `virtual` biar pointer umum bisa manggil aksi spesifik tiap child class pas runtime.
4. **Abstraction**: Sembunyiin kerumitan di balik layar, sediain interface simpel buat yang mau make class-nya.

---

## Cara Compile & Run di Terminal

Buka terminal, masuk ke folder materi yang mau dicoba, terus compile kodenya:

```bash
# Contoh nyoba materi 01
cd 01_class_and_object
g++ -std=c++17 main.cpp -o main.exe
./main.exe

# Contoh nyoba materi 09 (multi-file)
cd ../09_separate_files
g++ -std=c++17 *.cpp -o main.exe
./main.exe
```
