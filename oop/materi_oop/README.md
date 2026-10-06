# 4 Pilar OOP C++ (Object-Oriented Programming)

Repositori ini berisi implementasi dan penjelasan lengkap mengenai **4 Pilar Utama Object-Oriented Programming (OOP)** menggunakan bahasa C++.

---

## 4 Pilar Utama OOP

| No | Pilar OOP | Konsep Utama | Folder & Kode |
| :---: | :--- | :--- | :--- |
| 1 | **Abstraction** (Abstraksi) | Menyembunyikan kerumitan implementasi & mendefinisikan interface menggunakan *pure virtual function* (`= 0`). | [`Abstraction/main.cpp`](./Abstraction/main.cpp) |
| 2 | **Polymorphism** (Polimorfisme) | Memungkinkan pemanggilan fungsi secara dinamis saat runtime (*dynamic dispatch*) melalui pointer/reference base class (`virtual`, `override`). | [`Polymorphism/main.cpp`](./Polymorphism/main.cpp) |
| 3 | **Encapsulation** (Enkapsulasi) | Mengamankan data dengan hak akses `private`, serta menyediakan akses teratur melalui Getter dan Setter dengan validasi. | [`Encapsulation/main.cpp`](./Encapsulation/main.cpp) |
| 4 | **Inheritance** (Pewarisan) | Menurunkan properti dan method dari parent class (base) ke child class (derived) untuk efisiensi dan reusabilitas kode. | [`Inheritance/main.cpp`](./Inheritance/main.cpp) |

---

## Struktur Folder

```text
belajar_oop/
├── Abstraction/
│   ├── main.cpp
│   └── README.md
├── Encapsulation/
│   ├── main.cpp
│   └── README.md
├── Inheritance/
│   ├── main.cpp
│   └── README.md
├── Polymorphism/
│   ├── main.cpp
│   └── README.md
└── README.md
```

---

## Cara Compile & Run

Masuk ke folder pilar yang ingin dijalankan, lalu compile menggunakan compiler C++ (misal `g++`):

```bash
# 1. Abstraction
cd Abstraction
g++ -std=c++17 main.cpp -o main
./main

# 2. Polymorphism
cd ../Polymorphism
g++ -std=c++17 main.cpp -o main
./main

# 3. Encapsulation
cd ../Encapsulation
g++ -std=c++17 main.cpp -o main
./main

# 4. Inheritance
cd ../Inheritance
g++ -std=c++17 main.cpp -o main
./main
```
