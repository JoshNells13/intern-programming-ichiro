#ifndef STRIKER_HPP
#define STRIKER_HPP

#include "Robot.hpp"
#include "CameraSensor.hpp"
#include "Exceptions.hpp"
#include "Ball.hpp"

enum class RobotAction {
    SEARCH_BALL,
    APPROACH_BALL,
    ALIGN_TO_GOAL,
    KICK
};

class Striker : public Robot {
private:
    CameraSensor camera; // Composition (HAS-A)
    std::vector<GridCoord> currentVisionArea;
    bool ballVisible;
    Vector2D lastKnownBallPos;
    bool ballInFront;
    RobotAction nextAction;

public:
    Striker();
    Striker(double x, double y, double orientationDeg = 0.0);

    const CameraSensor& getCamera() const;
    const std::vector<GridCoord>& getCurrentVisionArea() const;
    RobotAction getNextAction() const;
    bool isBallVisible() const;

    // Sense: membaca data melalui kamera
    void sense(const Ball& ball);
    void sense() override;

    // Think: menentukan aksi berikutnya
    void think() override;

    // Act: mengeksekusi aksi
    void act(Ball& ball);
    void act() override;
};

#endif
