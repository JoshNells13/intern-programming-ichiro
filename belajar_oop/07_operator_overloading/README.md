# Materi 07: Operator Overloading

## 1. Konsep Inti

Operator Overloading itu cara "ngajarin" operator bawaan C++ (kayak `+`, `-`, `==`, atau `<<`) biar paham gimana cara memproses objek buatan kita sendiri.

Tujuannya biar sintaks kode jadi jauh lebih bersih, rapi, dan natural dibaca.
Daripada ribet nulis `Vector2D c = a.add(b);`, lebih enak langsung nulis `Vector2D c = a + b;`.

---

## 2. Cara Bikin Operator Overloading

Tinggal bikin fungsi khusus dengan nama `operator<simbol>`:

- **Operator Tambah (`+`)**:
  ```cpp
  Vector2D operator+(const Vector2D& other) const {
      return Vector2D(x + other.x, y + other.y);
  }
  ```
- **Operator Perbandingan Sama Dengan (`==`)**:
  ```cpp
  bool operator==(const Vector2D& other) const {
      return (x == other.x) && (y == other.y);
  }
  ```
- **Operator Cetak Terminal (`<<`)**:
  Dijadiin `friend` biar bisa langsung colok bareng `std::cout`:
  ```cpp
  friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
      os << "(" << vec.x << ", " << vec.y << ")";
      return os;
  }
  ```

---

## 3. Bedah Alur File main.cpp

1. Bikin objek koordinat posisi robot `posRobot(10.5, 20.0)` dan vektor perpindahan `velocity(2.0, -1.5)`.
2. Jumlahin keduanya langsung: `Vector2D newPos = posRobot + velocity;`.
3. Print hasilnya langsung ke terminal pake `std::cout << newPos`.
4. Cek apakah target tercapai pake `if (newPos == target)`.

---

## 4. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Posisi Awal   : (10.5, 20)
Kecepatan     : (2, -1.5)
Posisi Baru   : (12.5, 18.5)
Robot telah mencapai posisi target!
```
