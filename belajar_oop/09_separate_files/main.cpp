#include <iostream>
#include <vector>
#include <memory>
#include "Robot.hpp"
#include "StrikerRobot.hpp"

int main() {
    // Alur 1: Instansiasi objek dari class terpisah
    Robot baseBot("Ichiro-Base", 75);
    StrikerRobot strikerBot("Ichiro-Striker", 90, 300);

    // Alur 2: Eksekusi method spesifik masing-masing objek
    baseBot.displayInfo();
    baseBot.charge(15);

    std::cout << "\n";
    strikerBot.displayInfo();
    strikerBot.kickBall();

    // Alur 3: Runtime Polymorphism dengan pointer base class
    std::cout << "\n--- Uji Polimorfisme Multi-File ---\n";
    std::vector<std::unique_ptr<Robot>> team;
    team.push_back(std::make_unique<Robot>("Ichiro-Observer", 50));
    team.push_back(std::make_unique<StrikerRobot>("Ichiro-Forward", 85, 275));

    for (const auto& robot : team) {
        robot->displayInfo();
    }

    return 0;
}
