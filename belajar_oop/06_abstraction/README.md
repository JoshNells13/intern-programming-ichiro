# Materi 06: Abstraction and Interfaces

## 1. Konsep Inti

Abstraction (Abstraksi) adalah cara nyembunyiin detail teknis yang ribet dan cuma nampilin tombol atau fungsi pentingnya aja.

Contoh simpel: Pas nyalain TV pake remote control, kita cukup neken tombol Power tanpa perlu pusing mikirin gimana gelombang sinyal inframerah atau sirkuit internalnya bekerja.

### Istilah Penting:
- **Pure Virtual Function**: Fungsi yang berujung `= 0;` dan sengaja ga dikasih isi body di class induk. Ini adalah "kontrak wajib" yang harus diisi sama class anak.
  ```cpp
  virtual void calibrate() = 0;
  ```
- **Abstract Class / Interface**: Class yang punya minimal satu pure virtual function. Class ini **ga bisa diinstansiasi langsung jadi objek**. Tujuannya murni sebagai standarisasi kontrak buat class turunannya.

---

## 2. Bedah Alur File main.cpp

1. Bikin interface `Sensor` yang netapin kontrak standar: semua sensor wajib punya `calibrate()`, `readData()`, dan `getSensorName()`.
2. Class `CameraVision` dan `IMUSensor` ngasih implementasi nyata sesuai cara kerja hardware sensor masing-masing.
3. Bikin fungsi diagnosa umum `runDiagnostic(Sensor* sensor)`. Fungsi ini bisa nerima sensor apa pun dan langsung jalanin diagnosa tanpa perlu tau detail fisik sensornya.

---

## 3. Cara Nyoba & Output

Jalankan perintah ini di terminal:

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Expected Output:
```text
--- Diagnostik Sensor: Camera Vision HD ---
[CameraVision] Kalibrasi white balance dan FOV selesai.
Output Data: 1920

--- Diagnostik Sensor: 6-DOF IMU Sensor ---
[IMU] Kalibrasi gyro offset dan accelerometer selesai.
Output Data: 9.81
```
