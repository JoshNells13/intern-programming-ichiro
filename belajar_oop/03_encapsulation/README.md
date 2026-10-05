# Materi 03: Encapsulation and Data Hiding

## 1. Konsep Inti

Encapsulation intinya ngebungkus dan ngunci variabel penting ke dalam status `private` biar ga bisa diotak-atik sembarangan dari luar class.

### Kenapa Butuh Banget Ini?
Bayangin kalo ada class rekening bank (`BankAccount`). Kalo variabel `balance` (saldo) dibiarin `public`, siapa aja di fungsi `main()` bisa nulis `account.balance = -99999999;` dan ngerusak data saldo gitu aja.

Solusinya pake Encapsulation:
1. Variabel `balance` disembunyiin rapat di blok `private:`.
2. Sediain jalur resmi berupa **Getter** buat baca nilai (misal `getBalance()`).
3. Sediain jalur resmi berupa **Setter / Method Transaksi** buat ngubah nilai pake validasi aturan bisnis (misal `withdraw()`, saldo ga bakal bisa ditarik kalo uang ga mencukupi).

---

## 2. Bedah Alur File main.cpp

1. Bikin rekening dengan nomor `"ICHIRO-BANK-001"` dan saldo awal `Rp 1.000.000`.
2. Baca saldo via `account.getBalance()`.
3. Setor `Rp 500.000` via `account.deposit()`. Saldo naik jadi `Rp 1.500.000`.
4. Tarik `Rp 300.000` via `account.withdraw()`. Saldo tersisa `Rp 1.200.000`.
5. Coba tarik `Rp 2.000.000`. Karena saldo ga cukup, method otomatis nolak transaksi sehingga saldo rekening tetep aman.

---

## 3. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
Nomor Rekening : ICHIRO-BANK-001
Saldo Awal     : Rp1000000

Deposit: Rp500000 | Saldo baru: Rp1500000
Tarik dana: Rp300000 | Sisa saldo: Rp1200000
Gagal tarik dana: Saldo tidak mencukupi.
```
