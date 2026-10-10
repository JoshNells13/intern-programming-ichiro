#include "Striker.hpp"
#include "StrikerState.hpp"
#include "Field.hpp"
#include <iostream>

Striker::Striker()
    : Robot(), ballVisible(false), lastKnownBallPos(0, 0), ballInFront(false),
      currentState(new SearchState()), kickMode(1), lastKickType("-") {}

Striker::Striker(double x, double y, double orientationDeg)
    : Robot(x, y, orientationDeg), ballVisible(false), lastKnownBallPos(0, 0), ballInFront(false),
      currentState(new SearchState()), kickMode(1), lastKickType("-") {}

Striker::Striker(const Striker& other)
    : Robot(other), camera(other.camera), currentVisionArea(other.currentVisionArea),
      ballVisible(other.ballVisible), lastKnownBallPos(other.lastKnownBallPos),
      ballInFront(other.ballInFront), currentState(nullptr), kickMode(other.kickMode),
      lastKickType(other.lastKickType) {
    if (other.currentState) {
        std::string name = other.currentState->getName();
        if (name == "SEARCH_BALL") currentState = new SearchState();
        else if (name == "APPROACH_BALL") currentState = new ApproachState();
        else if (name == "ALIGN_TO_GOAL") currentState = new AlignState();
        else if (name == "KICK") currentState = new KickState();
    }
}

Striker& Striker::operator=(const Striker& other) {
    if (this != &other) {
        Robot::operator=(other);
        camera = other.camera;
        currentVisionArea = other.currentVisionArea;
        ballVisible = other.ballVisible;
        lastKnownBallPos = other.lastKnownBallPos;
        ballInFront = other.ballInFront;
        delete currentState;
        currentState = nullptr;
        if (other.currentState) {
            std::string name = other.currentState->getName();
            if (name == "SEARCH_BALL") currentState = new SearchState();
            else if (name == "APPROACH_BALL") currentState = new ApproachState();
            else if (name == "ALIGN_TO_GOAL") currentState = new AlignState();
            else if (name == "KICK") currentState = new KickState();
        }
    }
    return *this;
}

Striker::~Striker() {
    delete currentState;
}

const CameraSensor& Striker::getCamera() const { return camera; }
const std::vector<GridCoord>& Striker::getCurrentVisionArea() const { return currentVisionArea; }
bool Striker::isBallVisible() const { return ballVisible; }
bool Striker::isBallInFront() const { return ballInFront; }
Vector2D Striker::getLastKnownBallPos() const { return lastKnownBallPos; }

std::string Striker::getStateName() const {
    return currentState ? currentState->getName() : "IDLE";
}

int Striker::getKickMode() const { return kickMode; }
void Striker::setKickMode(int mode) { kickMode = mode; }
std::string Striker::getLastKickType() const { return lastKickType; }
void Striker::setLastKickType(const std::string& type) { lastKickType = type; }

void Striker::changeState(StrikerState* newState) {
    delete currentState;
    currentState = newState;
}

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
    if (ballVisible && currentState && currentState->getName() == "SEARCH_BALL") {
        changeState(new ApproachState());
    }
}

void Striker::act(Ball& ball) {
    if (currentState) {
        currentState->handle(*this, ball);
    }
}

void Striker::act() {}
