#include <iostream>
#include <string>

// Parent class
class Robot {
protected:
    std::string name;
    int battery;

public:
    Robot(std::string rName, int rBattery) : name(rName), battery(rBattery) {}

    void status() const {
        std::cout << "Robot: " << name << " | Baterai: " << battery << "%\n";
    }
};

// Child class 1
class StrikerRobot : public Robot {
private:
    int kickPower;

public:
    StrikerRobot(std::string rName, int rBattery, int power)
        : Robot(rName, rBattery), kickPower(power) {}

    void kickBall() {
        std::cout << name << " menendang bola dengan kekuatan " << kickPower << " N!\n";
    }
};

// Child class 2
class GoalkeeperRobot : public Robot {
private:
    int saveReactionMs;

public:
    GoalkeeperRobot(std::string rName, int rBattery, int reaction)
        : Robot(rName, rBattery), saveReactionMs(reaction) {}

    void diveToSave() {
        std::cout << name << " menangkap bola dengan reaksi " << saveReactionMs << " ms!\n";
    }
};

int main() {
    // Alur: Buat objek child -> panggil method parent & method spesifik child
    StrikerRobot striker("Ichiro-Striker", 90, 250);
    GoalkeeperRobot keeper("Ichiro-Keeper", 95, 120);

    striker.status();
    striker.kickBall();

    std::cout << "\n";

    keeper.status();
    keeper.diveToSave();

    return 0;
}
