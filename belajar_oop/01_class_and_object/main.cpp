#include <iostream>
#include <string>

class Robot {
public:
    std::string name;
    int batteryLevel;

    void displayInfo() {
        std::cout << "Robot: " << name << " | Baterai: " << batteryLevel << "%\n";
    }

    void charge(int amount) {
        batteryLevel += amount;
        if (batteryLevel > 100) batteryLevel = 100;
        std::cout << name << " sedang di-charge. Sisa: " << batteryLevel << "%\n";
    }
};

int main() {
    // Alur: Buat objek -> inisialisasi data -> panggil method
    Robot robot1;
    robot1.name = "Ichiro-01";
    robot1.batteryLevel = 80;

    Robot robot2;
    robot2.name = "Ichiro-02";
    robot2.batteryLevel = 45;

    robot1.displayInfo();
    robot2.displayInfo();

    robot2.charge(30);
    robot2.displayInfo();

    return 0;
}
