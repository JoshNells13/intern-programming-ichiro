#include "StrikerState.hpp"
#include "Striker.hpp"
#include "Ball.hpp"
#include "Field.hpp"
#include "Exceptions.hpp"
#include <cmath>

static int searchCount = 0;

void SearchState::handle(Striker& striker, Ball& ball) {
    if (striker.isBallVisible()) {
        searchCount = 0;
        striker.changeState(new ApproachState());
    } else {
        searchCount++;
        // Muter 90 derajat setiap tick
        striker.rotateTowards(striker.getOrientation() + 90.0, 90.0);
        if (searchCount % 2 == 0 && striker.getPosition().x < 2.5) {
            striker.setPosition(striker.getPosition().x + 0.5, striker.getPosition().y);
        }
    }
}

void ApproachState::handle(Striker& striker, Ball& ball) {
    if (!striker.isBallVisible()) {
        striker.changeState(new SearchState());
        return;
    }

    int rRow, rCol, bRow, bCol;
    Field::worldToGrid(striker.getPosition(), rRow, rCol);
    Field::worldToGrid(ball.getPosition(), bRow, bCol);

    int targetRow = bRow;
    int targetCol = bCol - 1;

    // Jika robot sudah berada tepat di belakang bola
    if (rRow == targetRow && rCol == targetCol) {
        striker.setOrientation(0.0); // Hadapkan ke kanan (0 deg) ke arah gawang
        striker.changeState(new AlignState());
        return;
    }

    // Gerakkan robot mendekat ke posisi belakang bola (targetRow, targetCol)
    if (rCol < targetCol) {
        striker.setOrientation(0.0);
        striker.moveForward(0.5);
    } else if (rCol > targetCol) {
        striker.setOrientation(180.0);
        striker.moveForward(0.5);
    } else if (rRow < targetRow) {
        striker.setOrientation(270.0);
        striker.moveForward(0.5);
    } else if (rRow > targetRow) {
        striker.setOrientation(90.0);
        striker.moveForward(0.5);
    }
}

void AlignState::handle(Striker& striker, Ball& ball) {
    int rRow, rCol, bRow, bCol;
    Field::worldToGrid(striker.getPosition(), rRow, rCol);
    Field::worldToGrid(ball.getPosition(), bRow, bCol);

    // Pastikan robot menghadap kanan (0 deg) dan bola tepat 1 petak di depan robot
    if (rRow == bRow && rCol + 1 == bCol) {
        striker.setOrientation(0.0);
        striker.changeState(new KickState());
    } else {
        striker.changeState(new ApproachState());
    }
}

void KickState::handle(Striker& striker, Ball& ball) {
    if (!striker.isBallInFront()) {
        throw InvalidKickException();
    }

    // Tendang bola lurus ke arah gawang (x = 4.5, y = ball.y)
    Vector2D kickDir(1.0, 0.0);
    ball.kick(kickDir, 3.0);
}
