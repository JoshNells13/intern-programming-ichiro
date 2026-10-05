#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>

// Deklarasi Base Class Robot
class Robot {
protected:
    std::string name;
    int batteryLevel;

public:
    Robot(const std::string& name, int battery);
    virtual ~Robot() = default;

    virtual void displayInfo() const;
    void charge(int amount);

    std::string getName() const;
    int getBatteryLevel() const;
};

#endif
