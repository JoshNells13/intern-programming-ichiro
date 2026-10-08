#ifndef BALL_HPP
#define BALL_HPP

#include "Vector2D.hpp"

class Ball {
private:
    Vector2D position;
    Vector2D velocity;
    double speed;

public:
    Ball();
    Ball(double x, double y);

    Vector2D getPosition() const;
    void setPosition(const Vector2D& pos);

    double getSpeed() const;
    void kick(const Vector2D& dir, double initialSpeed = 3.0);
    void update();
    void stop();
};

#endif
