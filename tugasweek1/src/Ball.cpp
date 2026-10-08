#include "Ball.hpp"
#include <algorithm>

Ball::Ball() : position(0.0, 0.0), velocity(0.0, 0.0), speed(0.0) {}
Ball::Ball(double x, double y)
    : position(x, y), velocity(0.0, 0.0), speed(0.0) {}

Vector2D Ball::getPosition() const { return position; }
void Ball::setPosition(const Vector2D &pos) { position = pos; }
double Ball::getSpeed() const { return speed; }

void Ball::kick(const Vector2D &dir, double initialSpeed) {
  speed = initialSpeed;
  velocity = dir.normalized() * speed;
}

void Ball::update() {
  if (speed <= 0.0)
    return;
  position = position + velocity;
  speed = std::max(0.0, speed - 1.0);
  if (speed <= 0.0)
    stop();
  else
    velocity = velocity.normalized() * speed;
}

void Ball::stop() {
  speed = 0.0;
  velocity = Vector2D(0.0, 0.0);
}
