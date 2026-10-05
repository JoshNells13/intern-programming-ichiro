#ifndef STRIKER_ROBOT_HPP
#define STRIKER_ROBOT_HPP

#include "Robot.hpp"

// Deklarasi Derived Class StrikerRobot
class StrikerRobot : public Robot {
private:
    int kickPower;

public:
    StrikerRobot(const std::string& name, int battery, int power);

    void displayInfo() const override;
    void kickBall();
};

#endif
