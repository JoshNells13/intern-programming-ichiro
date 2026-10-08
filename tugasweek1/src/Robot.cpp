#include "Robot.hpp"
#include <algorithm>
#include <cmath>

Robot::Robot()
    : position(0.0, 0.0), orientation(0.0), speed(0.0), maxSpeed(0.5) {}

Robot::Robot(double x, double y, double initialOrientation)
    : position(x, y), orientation(Vector2D::normalizeAngle(initialOrientation)),
      speed(0.0), maxSpeed(0.5) {}

Vector2D Robot::getPosition() const { return position; }
void Robot::setPosition(const Vector2D &pos) { position = pos; }
void Robot::setPosition(double x, double y) { position = Vector2D(x, y); }

double Robot::getOrientation() const { return orientation; }
void Robot::setOrientation(double angleDeg) {
  orientation = Vector2D::normalizeAngle(angleDeg);
}

double Robot::getSpeed() const { return speed; }
void Robot::setSpeed(double spd) {
  if (spd < 0.0)
    speed = 0.0;
  else if (spd > maxSpeed)
    speed = maxSpeed;
  else
    speed = spd;
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
  double step = dist;
  if (step < 0.0)
    step = 0.0;
  if (step > maxSpeed)
    step = maxSpeed;

  double rad = orientation * PI / 180.0;
  position = position + Vector2D(std::cos(rad) * step, std::sin(rad) * step);
}
