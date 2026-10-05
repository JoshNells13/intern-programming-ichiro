# Materi 05: Polymorphism (Polimorfisme)

## 1. Konsep Inti

Polymorphism artinya "banyak bentuk". Konsep ini bikin kita bisa nampung berbagai macam objek anak yang beda-beda ke dalam satu wadah/tipe pointer induk yang sama. Pas method-nya dipanggil, C++ bakal otomatis manggil perilaku unik dari masing-masing objek aslinya (*Runtime Polymorphism*).

### Keyword Penting:
- **`virtual`**: Ditulis di fungsi parent class. Tujuannya ngasih tau compiler C++ biar nyari fungsi milik child class pas program lagi jalan (*Dynamic Binding*).
- **`override`**: Ditulis di fungsi child class buat mastiin fungsi itu beneran nimpa fungsi parent (biar ga salah ketik nama/parameter).
- **`virtual ~Robot() = default;`**: Wajib hukumnya di parent class! Biar pas objek child dihapus dari pointer parent, proses bersih-bersih memorinya tuntas dan ga ada kebocoran memori.

---

## 2. Bedah Alur File main.cpp

1. Punya base class `Robot` dengan fungsi `virtual void performAction()`.
2. Tiga child class (`StrikerRobot`, `DefenderRobot`, `RefereeRobot`) masing-masing meng-override fungsi tersebut dengan aksi khas mereka.
3. Di `main()`, bikin satu wadah vector bertipe pointer induk: `std::vector<std::unique_ptr<Robot>> team`.
4. Masukin ketiga jenis robot yang beda itu ke dalam satu vector yang sama.
5. Pas looping manggil `member->performAction()`, C++ secara cerdas manggil aksi unik tiap robot: Striker nembak bola, Defender ngeblok lawan, dan Wasit niup peluit.

---

## 3. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Striker berlari dan menembak ke gawang musuh!
Defender memblokir pergerakan lawan!
Referee meniup peluit tanda pelanggaran!
```
