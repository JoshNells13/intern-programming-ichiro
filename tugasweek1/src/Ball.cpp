#include "Ball.h"
#include <algorithm>

Ball::Ball() : position(0.0, 0.0), velocity(0.0, 0.0), speed(0.0), inMotion(false) {}

Ball::Ball(double x, double y) : position(x, y), velocity(0.0, 0.0), speed(0.0), inMotion(false) {}

Vector2D Ball::getPosition() const {
    return position;
}

void Ball::setPosition(const Vector2D& pos) {
    position = pos;
}

void Ball::setPosition(double x, double y) {
    position = Vector2D(x, y);
}

Vector2D Ball::getVelocity() const {
    return velocity;
}

double Ball::getSpeed() const {
    return speed;
}

bool Ball::isInMotion() const {
    return inMotion;
}

void Ball::kick(const Vector2D& direction, double initialSpeed) {
    Vector2D dirNorm = direction.normalized();
    speed = initialSpeed;
    velocity = dirNorm * speed;
    inMotion = (speed > 0.0);
}

void Ball::update() {
    if (!inMotion) return;

    // Gerakkan bola sesuai kecepatan saat ini
    position = position + velocity;

    // Mengalami penurunan kecepatan sebesar 1.0 m per tick
    speed = std::max(0.0, speed - 1.0);
    if (speed <= 0.0) {
        stop();
    } else {
        Vector2D dir = velocity.normalized();
        velocity = dir * speed;
    }
}

void Ball::stop() {
    speed = 0.0;
    velocity = Vector2D(0.0, 0.0);
    inMotion = false;
}
