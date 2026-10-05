# Materi 06: Abstraction and Interfaces

## 1. Konsep Dasar

Abstraction (Abstraksi) adalah pilar OOP yang berfokus pada menyembunyikan detail implementasi internal yang rumit dan hanya memperlihatkan antarmuka (interface) esensial kepada pengguna class.

Contoh nyata: Saat Anda mengendarai mobil, Anda cukup tahu cara menginjak pedal gas dan memutar setir, tanpa harus memikirkan proses pembakaran bahan bakar di dalam mesin.

## 2. Pure Virtual Function dan Abstract Class

- **Pure Virtual Function**: Fungsi virtual yang tidak memiliki implementasi (body) pada base class dan dideklarasikan dengan sintaks `= 0;`.
  ```cpp
  virtual void calibrate() = 0;
  ```
- **Abstract Class**: Class apa pun yang memiliki minimal satu pure virtual function. Abstract class **tidak dapat dibuat menjadi objek secara langsung** (`Sensor s;` akan menghasilkan error).
- **Interface**: Class yang seluruh method-nya adalah pure virtual functions dan bertindak murni sebagai "kontrak" yang wajib dipenuhi oleh class turunan.

## 3. Penjelasan Alur Program main.cpp

1. Class `Sensor` adalah abstract class yang mendefinisikan 3 kontrak antarmuka:
   - `calibrate()`
   - `readData()`
   - `getSensorName()`
2. `CameraVision` dan `IMUSensor` adalah concrete class yang mengimplementasikan ketiga method kontrak tersebut.
3. Fungsi `runDiagnostic(Sensor* sensor)` dapat menerima objek turunan sensor apa pun. Fungsi ini cukup tahu cara berinteraksi dengan antarmuka `Sensor` tanpa peduli detail teknis sensor kamera ataupun IMU.

## 4. Cara Kompilasi dan Eksekusi

```bash
g++ -std=c++17 main.cpp -o main.exe
./main.exe
```

### Output yang Diharapkan:
```text
--- Diagnostik Sensor: Camera Vision HD ---
[CameraVision] Kalibrasi white balance dan FOV selesai.
Output Data: 1920

--- Diagnostik Sensor: 6-DOF IMU Sensor ---
[IMU] Kalibrasi gyro offset dan accelerometer selesai.
Output Data: 9.81
```
