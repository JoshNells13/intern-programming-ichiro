#include <iostream>
#include <string>

// Abstract class (Interface): Pure virtual functions
class Sensor {
public:
    virtual ~Sensor() = default;

    virtual void calibrate() = 0;
    virtual double readData() = 0;
    virtual std::string getSensorName() const = 0;
};

class CameraVision : public Sensor {
public:
    void calibrate() override {
        std::cout << "[CameraVision] Kalibrasi white balance dan FOV selesai.\n";
    }

    double readData() override {
        return 1920.0;
    }

    std::string getSensorName() const override {
        return "Camera Vision HD";
    }
};

class IMUSensor : public Sensor {
public:
    void calibrate() override {
        std::cout << "[IMU] Kalibrasi gyro offset dan accelerometer selesai.\n";
    }

    double readData() override {
        return 9.81;
    }

    std::string getSensorName() const override {
        return "6-DOF IMU Sensor";
    }
};

// Fungsi penerima antarmuka abstrak
void runDiagnostic(Sensor* sensor) {
    std::cout << "--- Diagnostik Sensor: " << sensor->getSensorName() << " ---\n";
    sensor->calibrate();
    std::cout << "Output Data: " << sensor->readData() << "\n\n";
}

int main() {
    // Alur: Buat objek konkret -> lewatkan pointer ke fungsi antarmuka
    CameraVision cam;
    IMUSensor imu;

    runDiagnostic(&cam);
    runDiagnostic(&imu);

    return 0;
}
