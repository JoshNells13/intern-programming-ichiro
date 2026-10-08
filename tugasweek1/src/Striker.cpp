#include "Striker.hpp"
#include "Field.hpp"
#include <cmath>
#include <iostream>

Striker::Striker()
    : Robot(), ballVisible(false), lastKnownBallPos(0, 0), ballInFront(false), nextAction(RobotAction::SEARCH_BALL) {}

Striker::Striker(double x, double y, double orientationDeg)
    : Robot(x, y, orientationDeg), ballVisible(false), lastKnownBallPos(0, 0), ballInFront(false), nextAction(RobotAction::SEARCH_BALL) {}

const CameraSensor& Striker::getCamera() const { return camera; }
const std::vector<GridCoord>& Striker::getCurrentVisionArea() const { return currentVisionArea; }
RobotAction Striker::getNextAction() const { return nextAction; }
bool Striker::isBallVisible() const { return ballVisible; }

void Striker::sense(const Ball& ball) {
    int rRow, rCol, bRow, bCol;
    Field::worldToGrid(position, rRow, rCol);
    Field::worldToGrid(ball.getPosition(), bRow, bCol);

    currentVisionArea = camera.getVisionArea(rRow, rCol, orientation);
    ballVisible = camera.detectBall(currentVisionArea, bRow, bCol);

    if (ballVisible) {
        lastKnownBallPos = ball.getPosition();
        ballInFront = camera.isBallInFront(rRow, rCol, orientation, bRow, bCol);
    } else {
        ballInFront = false;
    }
}

void Striker::sense() {}

void Striker::think() {
    Vector2D goalPos(4.5, 0.0);

    if (ballInFront) {
        double bearingToGoal = Vector2D::calculateBearing(position, orientation, goalPos);
        if (std::abs(bearingToGoal) <= 45.0) {
            nextAction = RobotAction::KICK;
        } else {
            nextAction = RobotAction::ALIGN_TO_GOAL;
        }
    } else if (ballVisible) {
        nextAction = RobotAction::APPROACH_BALL;
    } else {
        nextAction = RobotAction::SEARCH_BALL;
    }
}

void Striker::act(Ball& ball) {
    Vector2D goalPos(4.5, 0.0);

    switch (nextAction) {
        case RobotAction::SEARCH_BALL:
            rotateTowards(orientation + 45.0);
            break;

        case RobotAction::APPROACH_BALL: {
            double targetAngle = (lastKnownBallPos - position).angleDeg();
            double bearing = Vector2D::calculateBearing(position, orientation, lastKnownBallPos);
            if (std::abs(bearing) > 20.0) {
                rotateTowards(targetAngle, 45.0);
            } else {
                moveForward(0.5);
            }
            break;
        }

        case RobotAction::ALIGN_TO_GOAL: {
            double goalAngle = (goalPos - position).angleDeg();
            rotateTowards(goalAngle, 45.0);
            break;
        }

        case RobotAction::KICK: {
            if (!ballInFront) {
                throw InvalidKickException();
            }
            Vector2D kickDir = goalPos - ball.getPosition();
            ball.kick(kickDir, 3.0);
            break;
        }
    }
}

void Striker::act() {}
