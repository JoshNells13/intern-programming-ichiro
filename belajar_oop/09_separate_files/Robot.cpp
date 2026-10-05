#include "Robot.hpp"
#include <iostream>

// Implementasi constructor
Robot::Robot(const std::string& name, int battery)
    : name(name), batteryLevel(battery > 100 ? 100 : (battery < 0 ? 0 : battery)) {}

// Implementasi method
void Robot::displayInfo() const {
    std::cout << "[Robot] Nama: " << name << " | Baterai: " << batteryLevel << "%\n";
}

void Robot::charge(int amount) {
    if (amount > 0) {
        batteryLevel += amount;
        if (batteryLevel > 100) batteryLevel = 100;
        std::cout << name << " di-charge +" << amount << "% | Sisa: " << batteryLevel << "%\n";
    }
}

std::string Robot::getName() const {
    return name;
}

int Robot::getBatteryLevel() const {
    return batteryLevel;
}
