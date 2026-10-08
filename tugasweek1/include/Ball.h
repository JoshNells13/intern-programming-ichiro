#ifndef BALL_H
#define BALL_H

#include "Vector2D.h"

class Ball {
private:
    Vector2D position;
    Vector2D velocity; // meter per tick
    double speed;      // besar kecepatan dalam m/tick
    bool inMotion;

public:
    Ball();
    Ball(double x, double y);

    Vector2D getPosition() const;
    void setPosition(const Vector2D& pos);
    void setPosition(double x, double y);

    Vector2D getVelocity() const;
    double getSpeed() const;
    bool isInMotion() const;

    // Menendang bola dengan arah tertentu (kecepatan awal 3.0 m/tick)
    void kick(const Vector2D& direction, double initialSpeed = 3.0);

    // Update posisi dan penurunan kecepatan 1.0 m/tick per tick
    void update();

    void stop();
};

#endif // BALL_H
