# MAINAN ROBOT - Simulasi AI Striker Robot Soccer (ICHIRO ITS)

Proyek simulasi robot soccer humanoid 2D berbasis terminal untuk robot Striker (Penyerang) otonom. Robot bertugas mencari posisi bola di lapangan, mendekati bola, mengatur sudut tembak, dan menendang bola hingga masuk ke gawang lawan.

---

## Fitur Utama

### Level 1: Core Simulation & OOP
- **Vector2D Helper**: Modul matematika 2D untuk menghitung jarak, bearing angle, dan normalisasi sudut -180° sampai 180° sesuai prinsip DRY.
- **Field ($9\text{m} \times 6\text{m}$)**: Representasi lapangan grid ASCII $18 \times 12$ petak ($1\text{ petak} = 0.5\text{m} \times 0.5\text{m}$) dengan gawang lawan (`#`).
- **Ball**: Objek bola dengan fisika deselerasi nyata ($3 \to 2 \to 1 \to 0\text{ m/tick}$).
- **Abstract Class Robot**: Kelas induk dengan enkapsulasi (getter/setter tervalidasi) dan pembatasan kecepatan maksimum 0.5 m/tick.

### Level 2: Sensor Kamera & Exception Handling
- **Camera Sensor (Vision Segitiga)**: Implementasi sensor kamera (Composition / HAS-A) dengan jangkauan pandang segitiga (tinggi 1.5m, alas 3.5m). Pembacaan bola dilakukan murni melalui sensor kamera tanpa membaca data global simulator.
- **Exception Handling**: Penanganan aksi tidak valid melalui try-catch (misalnya saat robot mencoba menendang bola yang belum berada di posisi depan melalui `InvalidKickException`).

### Level 3: Extra Features
- **Interactive User Input**: Input interaktif koordinat awal robot, sudut hadap, dan posisi bola saat program dijalankan.
- **File Konfigurasi (`config.txt`)**: Penentuan posisi awal Striker dan Bola melalui file teks.
- **State Pattern**: Pengelolaan alur perilaku Striker menggunakan State Pattern (`SearchState` -> `ApproachState` -> `AlignState` -> `KickState`).
- **Arah Tendangan**: Kemampuan eksekusi tendangan lurus maupun miring (diagonal).
- **Unit Testing**: Pengujian independen untuk kalkulasi matematika vektor dan fisika perlambatan bola.

---

## Panduan Kompilasi dan Eksekusi

Pastikan terminal berada di direktori `tugasweek1`.

### 1. Simulasi Utama
```bash
# Kompilasi
g++ -Iinclude src/Ball.cpp src/CameraSensor.cpp src/ConfigLoader.cpp src/Field.cpp src/Main.cpp src/Robot.cpp src/Simulator.cpp src/Striker.cpp src/StrikerState.cpp -o main.exe

# Menjalankan di Git Bash / Linux
./main.exe

# Menjalankan di CMD / PowerShell
main.exe
```

Saat program dijalankan, masukkan koordinat sesuai permintaan di terminal:
```text
Masukkan posisi Robot (x y): -1.5 0.0
Masukkan sudut hadap Robot (derajat): 0.0
Masukkan posisi Bola (x y): 1.0 -0.5
```

### 2. Unit Testing
```bash
g++ -Iinclude src/UnitTest.cpp src/Ball.cpp -o test.exe
./test.exe
```

---

## Arti Simbol Grid

| Simbol | Deskripsi |
|:---:|---|
| `R` | Robot Striker |
| `@` | Area jarak pandang sensor kamera segitiga (Field of View) |
| `O` | Bola |
| `#` | Gawang lawan di sisi kanan ($x = 4.5\text{m}$) |
| `.` | Area kosong lapangan |

---

## Alur State AI Striker

```mermaid
stateDiagram-v2
    [*] --> SearchState : Mulai Simulasi
    SearchState --> ApproachState : Bola Terdeteksi oleh Sensor Kamera (@)
    SearchState --> SearchState : Berputar dan Menjelajah Lapangan
    ApproachState --> SearchState : Bola Hilang dari Pandangan
    ApproachState --> AlignState : Robot Berada Tepat di Belakang Bola
    ApproachState --> ApproachState : Bergerak Mendekati Posisi Tembak
    AlignState --> KickState : Bola Tepat di Depan Robot Menghadap Gawang
    AlignState --> ApproachState : Posisi Bola Berubah
    KickState --> [*] : Menendang Bola Masuk Gawang (GOAL!)
```

---

## Diagram Kelas (Arsitektur OOP)

```mermaid
classDiagram
    direction TB

    class Vector2D {
        +double x
        +double y
        +distanceTo(Vector2D) double
        +angleDeg() double
        +normalizeAngle(double)$ double
        +calculateBearing(Vector2D, double, Vector2D)$ double
    }

    class Field {
        +int ROWS$
        +int COLS$
        +double CELL_SIZE$
        -char grid[12][18]
        +worldToGrid(Vector2D, int, int)$ bool
        +gridToWorld(int, int)$ Vector2D
        +isGoal(Vector2D)$ bool
        +display()
    }

    class Ball {
        -Vector2D position
        -Vector2D velocity
        -double speed
        +getPosition() Vector2D
        +setPosition(Vector2D)
        +kick(Vector2D, double)
        +update()
        +stop()
    }

    class CameraSensor {
        +getVisionArea(int, int, double) vector
        +detectBall(vector, int, int) bool
        +isBallInFront(int, int, double, int, int) bool
    }

    class Robot {
        <<abstract>>
        #Vector2D position
        #double orientation
        #double speed
        #double maxSpeed
        +sense()*
        +think()*
        +act()*
        +rotateTowards(double, double)
        +moveForward(double)
    }

    class Striker {
        -CameraSensor camera
        -StrikerState* currentState
        -bool ballVisible
        -bool ballInFront
        -Vector2D lastKnownBallPos
        +sense(Ball)
        +think()
        +act(Ball)
        +changeState(StrikerState*)
        +getStateName() string
    }

    class StrikerState {
        <<interface>>
        +handle(Striker, Ball)*
        +getName()* string
    }

    class SearchState {
        +handle(Striker, Ball)
        +getName() string
    }

    class ApproachState {
        +handle(Striker, Ball)
        +getName() string
    }

    class AlignState {
        +handle(Striker, Ball)
        +getName() string
    }

    class KickState {
        +handle(Striker, Ball)
        +getName() string
    }

    class Simulator {
        -Field field
        -Ball ball
        -Striker striker
        -int tick
        -int maxTicks
        -bool goalScored
        +step()
        +run()
        +render()
        +isGoal() bool
    }

    class RobotException {
        #string message
        +what() char*
    }

    class InvalidKickException {
        +InvalidKickException(string)
    }

    %% Hierarki & Relasi Utama
    Robot <|-- Striker : Inheritance (is-a)
    Robot *-- Vector2D : Composition
    Ball *-- Vector2D : Composition

    %% Komposisi Sensor & Komponen Simulator
    Striker *-- CameraSensor : Composition (has-a)
    Simulator *-- Field : Composition
    Simulator *-- Ball : Composition
    Simulator *-- Striker : Composition

    %% State Pattern
    Striker o-- StrikerState : Aggregation (State Pattern)
    StrikerState <|.. SearchState : Realization
    StrikerState <|.. ApproachState : Realization
    StrikerState <|.. AlignState : Realization
    StrikerState <|.. KickState : Realization

    %% Relasi Ketergantungan (Dependency)
    Striker ..> Ball : Dependency (Senses & Acts)
    StrikerState ..> Striker : Dependency (Controls)
    StrikerState ..> Ball : Dependency (Manipulates)
    KickState ..> InvalidKickException : Throws
    RobotException <|-- InvalidKickException : Inheritance
```

---

## Pernyataan Penggunaan AI

AI digunakan sebagai asisten pemrograman untuk membantu:
- Penataan struktur modular C++ dan header `.hpp`.
- Perhitungan geometris area vision kamera segitiga.
- Pembuatan visualisasi diagram Mermaid pada dokumentasi.
Seluruh logika inti algoritma, validasi OOP, enkapsulasi, dan eksekusi program telah diverifikasi dan diuji sesuai spesifikasi tugas.
