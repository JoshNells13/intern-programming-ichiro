#include "Vector2D.hpp"
#include "Ball.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

void testVectorMath() {
    Vector2D v1(3.0, 4.0);
    assert(std::abs(v1.length() - 5.0) < 1e-4);

    Vector2D v2(0.0, 0.0);
    assert(std::abs(v1.distanceTo(v2) - 5.0) < 1e-4);

    double normAngle = Vector2D::normalizeAngle(200.0);
    assert(std::abs(normAngle - (-160.0)) < 1e-4);

    double bearing = Vector2D::calculateBearing(Vector2D(0, 0), 0.0, Vector2D(0, 5.0));
    assert(std::abs(bearing - 90.0) < 1e-4);

    std::cout << "[PASS] Vector2D Math Tests\n";
}

void testBallPhysics() {
    Ball ball(0.0, 0.0);
    ball.kick(Vector2D(1.0, 0.0), 3.0);

    assert(std::abs(ball.getSpeed() - 3.0) < 1e-4);

    ball.update(); // Tick 1 (speed jadi 2.0)
    assert(std::abs(ball.getSpeed() - 2.0) < 1e-4);
    assert(std::abs(ball.getPosition().x - 3.0) < 1e-4);

    ball.update(); // Tick 2 (speed jadi 1.0)
    assert(std::abs(ball.getSpeed() - 1.0) < 1e-4);
    assert(std::abs(ball.getPosition().x - 5.0) < 1e-4);

    ball.update(); // Tick 3 (speed jadi 0.0)
    assert(std::abs(ball.getSpeed() - 0.0) < 1e-4);
    assert(std::abs(ball.getPosition().x - 6.0) < 1e-4);

    std::cout << "[PASS] Ball Physics Tests\n";
}

int main() {
    testVectorMath();
    testBallPhysics();
    std::cout << "Semua Unit Test Berhasil!\n";
    return 0;
}
