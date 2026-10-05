# Materi 03: Encapsulation and Data Hiding

## 1. Konsep Dasar

Encapsulation (Pembungkusan) adalah pilar OOP yang menggabungkan data (variabel) dan method (fungsi yang beroperasi pada data tersebut) ke dalam satu wadah (class), sekaligus menyembunyikan detail internal dari akses langsung pihak luar.

### Mengapa Encapsulation Sangat Penting?
1. **Integritas Data (Data Protection)**: Mencegah manipulasi variabel secara tidak sah atau tidak logis (misal: saldo bank tidak boleh bernilai negatif secara sembarangan).
2. **Fleksibilitas & Maintainability**: Implementasi internal class dapat diubah sewaktu-waktu tanpa merusak kode luar yang memanggilnya.
3. **Read-Only / Write-Only Access**: Mengontrol variabel mana yang hanya boleh dibaca (hanya ada Getter) atau hanya boleh diubah (hanya ada Setter).

## 2. Implementasi Getter dan Setter

- **Getter**: Method publik dengan keyword `const` yang mengembalikan nilai atribut privat tanpa mengubahnya.
- **Setter**: Method publik yang menerima argumen baru dan memvalidasinya sebelum disimpan ke atribut privat.

```cpp
class BankAccount {
private:
    double balance; // Tidak bisa diakses langsung dari main()

public:
    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) { // Validasi logika bisnis
            balance += amount;
        }
    }
};
```

## 3. Penjelasan Alur Program main.cpp

1. Atribut `accountNumber` dan `balance` dideklarasikan di bawah blok `private:`.
2. Pada `main()`, kita tidak dapat menulis `account.balance = 500;` karena compiler akan menghasilkan error kompilasi (proteksi akses).
3. Untuk mengubah saldo, program memanggil method `deposit(500000)` dan `withdraw(300000)`.
4. Method `withdraw(2000000)` menolak transaksi karena jumlah penarikan lebih besar dari sisa saldo akun, sehingga integritas data akun tetap terjaga.

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
Nomor Rekening : ICHIRO-BANK-001
Saldo Awal     : Rp1000000

Deposit: Rp500000 | Saldo baru: Rp1500000
Tarik dana: Rp300000 | Sisa saldo: Rp1200000
Gagal tarik dana: Saldo tidak mencukupi.
```
