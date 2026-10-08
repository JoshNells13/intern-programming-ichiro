#include "StrikerState.hpp"
#include "Striker.hpp"
#include "Ball.hpp"
#include "Field.hpp"
#include "Exceptions.hpp"
#include <cmath>
#include <vector>

static int searchRotateCount = 0;

void SearchState::handle(Striker& striker, Ball& ball) {
    if (striker.isBallVisible()) {
        searchRotateCount = 0;
        striker.changeState(new ApproachState());
    } else {
        searchRotateCount++;
        striker.rotateTowards(striker.getOrientation() + 45.0);
        if (searchRotateCount % 4 == 0) {
            striker.moveForward(0.5);
        }
    }
}

void ApproachState::handle(Striker& striker, Ball& ball) {
    if (!striker.isBallVisible()) {
        striker.changeState(new SearchState());
        return;
    }

    if (striker.isBallInFront()) {
        striker.changeState(new AlignState());
        return;
    }

    Vector2D targetPos = striker.getLastKnownBallPos();
    double bearing = Vector2D::calculateBearing(striker.getPosition(), striker.getOrientation(), targetPos);

    if (std::abs(bearing) > 20.0) {
        double targetAngle = (targetPos - striker.getPosition()).angleDeg();
        striker.rotateTowards(targetAngle, 45.0);
    } else {
        striker.moveForward(0.5);
    }
}

void AlignState::handle(Striker& striker, Ball& ball) {
    if (!striker.isBallInFront()) {
        striker.changeState(new ApproachState());
        return;
    }

    // Cek apakah ada di antara 3 opsi tendangan (lurus, +45, -45) yang bisa langsung gol
    double currentHeading = striker.getOrientation();
    std::vector<double> candidates = {
        currentHeading,
        Vector2D::normalizeAngle(currentHeading + 45.0),
        Vector2D::normalizeAngle(currentHeading - 45.0)
    };

    bool canScore = false;
    for (double ang : candidates) {
        double rad = ang * PI / 180.0;
        double dx = std::cos(rad);
        double dy = std::sin(rad);

        if (dx > 0.1) {
            double distToGoalLine = 4.5 - ball.getPosition().x;
            double projectedY = ball.getPosition().y + (dy / dx) * distToGoalLine;
            if (projectedY >= -1.5 && projectedY <= 1.5) {
                canScore = true;
                break;
            }
        }
    }

    if (canScore) {
        striker.changeState(new KickState());
    } else {
        Vector2D goalCenter(4.5, 0.0);
        double targetAngle = (goalCenter - striker.getPosition()).angleDeg();
        striker.rotateTowards(targetAngle, 45.0);
    }
}

void KickState::handle(Striker& striker, Ball& ball) {
    if (!striker.isBallInFront()) {
        throw InvalidKickException();
    }

    double currentHeading = striker.getOrientation();

    // 3 opsi tendangan: Lurus, Miring Atas (+45), Miring Bawah (-45)
    std::vector<double> candidates = {
        currentHeading,
        Vector2D::normalizeAngle(currentHeading + 45.0),
        Vector2D::normalizeAngle(currentHeading - 45.0)
    };

    double bestAngle = currentHeading;
    double bestDistToCenter = 9999.0;

    for (double ang : candidates) {
        double rad = ang * PI / 180.0;
        double dx = std::cos(rad);
        double dy = std::sin(rad);

        if (dx > 0.1) {
            double distToGoalLine = 4.5 - ball.getPosition().x;
            double projectedY = ball.getPosition().y + (dy / dx) * distToGoalLine;

            if (projectedY >= -1.5 && projectedY <= 1.5) {
                double dist = std::abs(projectedY);
                if (dist < bestDistToCenter) {
                    bestDistToCenter = dist;
                    bestAngle = ang;
                }
            }
        }
    }

    double bestRad = bestAngle * PI / 180.0;
    Vector2D kickDir(std::cos(bestRad), std::sin(bestRad));
    ball.kick(kickDir, 3.0);
}
