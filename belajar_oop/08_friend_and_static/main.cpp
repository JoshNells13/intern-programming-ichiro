#include <iostream>
#include <string>

class Motor;

class Joint {
private:
    std::string jointName;
    double currentAngle;

    friend void inspectJointPrivate(const Joint& j);
    friend class Motor;

public:
    static int totalJoints; // Static variable

    Joint(std::string name, double angle) : jointName(name), currentAngle(angle) {
        totalJoints++;
    }

    ~Joint() {
        totalJoints--;
    }

    static int getTotalJoints() { // Static function
        return totalJoints;
    }
};

int Joint::totalJoints = 0;

void inspectJointPrivate(const Joint& j) {
    std::cout << "[Friend Function Inspection] Joint: " << j.jointName 
              << " | Angle: " << j.currentAngle << " deg\n";
}

class Motor {
public:
    void applyTorque(Joint& j, double torque) {
        std::cout << "[Motor] Menggerakkan joint " << j.jointName << " dengan torsi " << torque << " Nm.\n";
        j.currentAngle += torque * 0.1;
    }
};

int main() {
    // Alur 1: Cek static function sebelum dan sesudah instansiasi
    std::cout << "Jumlah awal joint: " << Joint::getTotalJoints() << "\n";

    Joint knee("Knee_Left", 45.0);
    Joint ankle("Ankle_Left", 10.0);

    std::cout << "Jumlah joint sekarang: " << Joint::getTotalJoints() << "\n\n";

    // Alur 2: Akses private via friend function & friend class
    inspectJointPrivate(knee);

    Motor servo;
    servo.applyTorque(knee, 15.0);

    inspectJointPrivate(knee);

    return 0;
}
