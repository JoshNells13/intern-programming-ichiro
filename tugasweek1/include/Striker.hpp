#ifndef STRIKER_HPP
#define STRIKER_HPP

#include "Robot.hpp"
#include "CameraSensor.hpp"
#include "Exceptions.hpp"
#include "Ball.hpp"
#include <vector>
#include <string>

class StrikerState;

class Striker : public Robot {
private:
    CameraSensor camera;
    std::vector<GridCoord> currentVisionArea;
    bool ballVisible;
    Vector2D lastKnownBallPos;
    bool ballInFront;
    StrikerState* currentState;

public:
    Striker();
    Striker(double x, double y, double orientationDeg = 0.0);
    Striker(const Striker& other);
    Striker& operator=(const Striker& other);
    ~Striker() override;

    const CameraSensor& getCamera() const;
    const std::vector<GridCoord>& getCurrentVisionArea() const;
    bool isBallVisible() const;
    bool isBallInFront() const;
    Vector2D getLastKnownBallPos() const;
    std::string getStateName() const;

    void changeState(StrikerState* newState);

    void sense(const Ball& ball);
    void sense() override;
    void think() override;
    void act(Ball& ball);
    void act() override;
};

#endif
