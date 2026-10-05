# Panduan Belajar Object-Oriented Programming (OOP) C++

Selamat datang di modul pembelajaran Object-Oriented Programming (OOP) dalam C++. Modul ini disusun per folder topik secara terstruktur, lengkap dengan implementasi kode mandiri dan dokumentasi README terperinci di setiap materi.

---

## Daftar Materi dan Navigasi

| No | Folder Materi | Topik Pembahasan | File Utama |
| :---: | :--- | :--- | :--- |
| 01 | [01_class_and_object](./01_class_and_object/) | Definisi Class, Pembuatan Object, Atribut, Method, dan Hak Akses Public. | [main.cpp](./01_class_and_object/main.cpp) |
| 02 | [02_constructor_destructor](./02_constructor_destructor/) | Default, Parameterized, dan Copy Constructor, Member Initializer List, serta Destructor Lifecycle. | [main.cpp](./02_constructor_destructor/main.cpp) |
| 03 | [03_encapsulation](./03_encapsulation/) | Data Hiding, Hak Akses Private, serta Getter dan Setter dengan Validasi Logika Bisnis. | [main.cpp](./03_encapsulation/main.cpp) |
| 04 | [04_inheritance](./04_inheritance/) | Pewarisan Sifat, Hak Akses Protected, dan Constructor Chaining Antara Base dan Derived Class. | [main.cpp](./04_inheritance/main.cpp) |
| 05 | [05_polymorphism](./05_polymorphism/) | Runtime Polymorphism, Keyword Virtual, Override, Virtual Table, dan Virtual Destructor. | [main.cpp](./05_polymorphism/main.cpp) |
| 06 | [06_abstraction](./06_abstraction/) | Abstract Class, Pure Virtual Functions (`= 0`), dan Desain Pola Interface. | [main.cpp](./06_abstraction/main.cpp) |
| 07 | [07_operator_overloading](./07_operator_overloading/) | Overload Operator Aritmatika (`+`), Komparasi (`==`), dan Stream I/O (`<<`). | [main.cpp](./07_operator_overloading/main.cpp) |
| 08 | [08_friend_and_static](./08_friend_and_static/) | Variabel dan Fungsi Static, serta Hak Akses Friend Function dan Friend Class. | [main.cpp](./08_friend_and_static/main.cpp) |
| 09 | [09_separate_files](./09_separate_files/) | Struktur Proyek Multi-File: Pemisahan Header (`.hpp`), Source (`.cpp`), dan Entry Point (`main.cpp`). | [main.cpp](./09_separate_files/main.cpp) |

---

## Ringkasan 4 Pilar Utama OOP

1. **Encapsulation (Pembungkusan)**: Menyatukan data dan method dalam class, serta menyembunyikan detail internal menggunakan `private` agar tidak bisa dimodifikasi secara sembarangan.
2. **Inheritance (Pewarisan)**: Memungkinkan class anak mewarisi kode dari class induk sehingga kode lebih modular dan terhindar dari duplikasi.
3. **Polymorphism (Banyak Bentuk)**: Memungkinkan satu interface/pointer umum memanggil implementasi spesifik dari berbagai class turunan saat runtime via `virtual`.
4. **Abstraction (Abstraksi)**: Menyembunyikan kompleksitas implementasi dan hanya mengekspos antarmuka penting melalui abstract class dan pure virtual functions.

---

## Petunjuk Cara Menjalankan Kode

Masuk ke dalam salah satu folder materi yang ingin dipelajari, lalu kompilasi `main.cpp` menggunakan compiler C++ (contoh: g++):

```bash
# Contoh 1: Menjalankan materi single file
cd 01_class_and_object
g++ -std=c++17 main.cpp -o main.exe
./main.exe

# Contoh 2: Menjalankan materi multi-file
cd ../09_separate_files
g++ -std=c++17 *.cpp -o main.exe
./main.exe
```

Setiap folder memiliki file `README.md` tersendiri yang membedah konsep teori, diagram alur eksekusi, serta ekspektasi output terminal.
