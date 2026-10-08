#include "Robot.h"
#include <algorithm>
#include <cmath>

Robot::Robot()
    : position(0.0, 0.0), orientation(0.0), speed(0.0), maxSpeed(0.5), currentAction(ActionType::IDLE) {}

Robot::Robot(double x, double y, double initialOrientation)
    : position(x, y), orientation(Vector2D::normalizeAngle(initialOrientation)),
      speed(0.0), maxSpeed(0.5), currentAction(ActionType::IDLE) {}

Vector2D Robot::getPosition() const {
    return position;
}

void Robot::setPosition(const Vector2D& pos) {
    position = pos;
}

void Robot::setPosition(double x, double y) {
    position = Vector2D(x, y);
}

double Robot::getOrientation() const {
    return orientation;
}

void Robot::setOrientation(double angleDeg) {
    orientation = Vector2D::normalizeAngle(angleDeg);
}

double Robot::getSpeed() const {
    return speed;
}

void Robot::setSpeed(double spd) {
    // Validasi kecepatan agar tidak melebihi kecepatan maksimal (0.5 m/tick)
    speed = std::clamp(spd, 0.0, maxSpeed);
}

ActionType Robot::getCurrentAction() const {
    return currentAction;
}

void Robot::setCurrentAction(ActionType action) {
    currentAction = action;
}

double Robot::getDistanceTo(const Vector2D& target) const {
    return position.distanceTo(target);
}

double Robot::getBearingTo(const Vector2D& target) const {
    return Vector2D::calculateBearing(position, orientation, target);
}

void Robot::rotateTowards(double targetAngleDeg, double maxStepDeg) {
    double diff = Vector2D::normalizeAngle(targetAngleDeg - orientation);
    if (std::abs(diff) <= maxStepDeg) {
        setOrientation(targetAngleDeg);
    } else if (diff > 0) {
        setOrientation(orientation + maxStepDeg);
    } else {
        setOrientation(orientation - maxStepDeg);
    }
}

void Robot::moveForward(double dist) {
    double step = std::clamp(dist, 0.0, maxSpeed);
    double rad = orientation * M_PI / 180.0;
    Vector2D forward(std::cos(rad), std::sin(rad));
    position = position + (forward * step);
}
