#ifndef ROBOT_H
#define ROBOT_H

#include "Vector2D.h"
#include <string>

enum class ActionType {
    IDLE,
    SEARCH_BALL,
    APPROACH_BALL,
    ALIGN_TO_GOAL,
    KICK
};

class Robot {
protected:
    Vector2D position;
    double orientation;    // Sudut hadap robot dalam derajat (-180 sampai 180, 0 = menghadap sumbu +X / kanan)
    double speed;          // Kecepatan maju robot (maksimal 0.5 m / tick)
    double maxSpeed;       // 0.5 m/tick
    ActionType currentAction;

public:
    Robot();
    Robot(double x, double y, double initialOrientation = 0.0);
    virtual ~Robot() = default;

    // Getter & Setter tervalidasi
    Vector2D getPosition() const;
    void setPosition(const Vector2D& pos);
    void setPosition(double x, double y);

    double getOrientation() const;
    void setOrientation(double angleDeg);

    double getSpeed() const;
    void setSpeed(double spd);

    ActionType getCurrentAction() const;
    void setCurrentAction(ActionType action);

    // Navigasi & Helper DRY
    double getDistanceTo(const Vector2D& target) const;
    double getBearingTo(const Vector2D& target) const;
    void rotateTowards(double targetAngleDeg, double maxStepDeg = 45.0);
    void moveForward(double dist);

    // Siklus Sense - Think - Act
    virtual void sense() = 0;
    virtual void think() = 0;
    virtual void act() = 0;
};

#endif // ROBOT_H
