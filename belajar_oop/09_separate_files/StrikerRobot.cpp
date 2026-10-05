#include "StrikerRobot.hpp"
#include <iostream>

// Implementasi constructor dengan constructor chaining ke base class
StrikerRobot::StrikerRobot(const std::string& name, int battery, int power)
    : Robot(name, battery), kickPower(power) {}

// Implementasi override method
void StrikerRobot::displayInfo() const {
    std::cout << "[StrikerRobot] Nama: " << name 
              << " | Baterai: " << batteryLevel 
              << "% | Kick Power: " << kickPower << " N\n";
}

void StrikerRobot::kickBall() {
    std::cout << name << " menendang bola dengan kekuatan " << kickPower << " N!\n";
}
