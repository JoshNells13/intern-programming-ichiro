#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Vector2D.hpp"

class Robot {
protected:
    Vector2D position;
    double orientation; // derajat (-180 s/d 180)
    double speed;       // maks 0.5 m/tick
    double maxSpeed;

public:
    Robot();
    Robot(double x, double y, double initialOrientation = 0.0);
    virtual ~Robot() = default;

    Vector2D getPosition() const;
    void setPosition(const Vector2D& pos);
    void setPosition(double x, double y);

    double getOrientation() const;
    void setOrientation(double angleDeg);

    double getSpeed() const;
    void setSpeed(double spd);

    void rotateTowards(double targetAngleDeg, double maxStepDeg = 45.0);
    void moveForward(double dist);

    virtual void sense() = 0;
    virtual void think() = 0;
    virtual void act() = 0;
};

#endif
