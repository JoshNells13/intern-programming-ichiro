# Materi 07: Operator Overloading

## 1. Konsep Dasar

Operator Overloading adalah fitur dalam C++ yang memungkinkan kita memberikan makna atau fungsi khusus pada operator bawaan (seperti `+`, `-`, `*`, `==`, `<<`, `[]`, dll.) ketika bekerja dengan tipe data buatan sendiri (class atau struct).

Tujuannya adalah membuat sintaks operasi pada objek terasa alami, bersih, dan intuitif layaknya bekerja dengan tipe data primitif seperti `int` atau `double`.

## 2. Cara Kerja Operator Overloading

Operator di-overload dengan mendefinisikan fungsi bernama `operator<simbol>`:

### A. Operator Aritmatika Biner (`+`)
```cpp
Vector2D operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}
```
Ketika kita menulis `a + b`, compiler mengubahnya menjadi pemanggilan fungsi: `a.operator+(b)`.

### B. Operator Komparasi (`==`)
```cpp
bool operator==(const Vector2D& other) const {
    return (x == other.x) && (y == other.y);
}
```

### C. Stream Insertion Operator (`<<`)
Operator `<<` digunakan bersama `std::cout`. Karena operand sebelah kiri adalah `std::ostream` dan bukan objek class kita, fungsi ini harus dibuat sebagai fungsi non-member atau `friend`:
```cpp
friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
```

## 3. Penjelasan Alur Program main.cpp

1. Class `Vector2D` menyimpan koordinat 2 dimensi `x` dan `y`.
2. Program mendefinisikan `posRobot` pada koordinat `(10.5, 20.0)` dan vektor perpindahan `velocity` sebesar `(2.0, -1.5)`.
3. Operasi penjumlahan vektor ditulis sangat ringkas: `Vector2D newPos = posRobot + velocity;`.
4. Objek `newPos` dapat langsung dicetak ke konsol dengan `std::cout << newPos` berkat overload operator `<<`.
5. Pengecekan posisi target dilakukan menggunakan operator `if (newPos == target)`.

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Posisi Awal   : (10.5, 20)
Kecepatan     : (2, -1.5)
Posisi Baru   : (12.5, 18.5)
Robot telah mencapai posisi target!
```
