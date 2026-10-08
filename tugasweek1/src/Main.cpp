#include "Vector2D.hpp"
#include "Ball.hpp"
#include "Field.hpp"
#include "Striker.hpp"
#include "Exceptions.hpp"
#include <iostream>

int main() {
    Field field;
    Ball ball(1.5, -1.0);
    Striker striker(-1.5, 0.0, 0.0);

    // Update indra penglihatan kamera
    striker.sense(ball);

    // Gambar area pandang sensor '@'
    const auto& vision = striker.getCurrentVisionArea();
    for (const auto& coord : vision) {
        field.setCell(coord.row, coord.col, '@');
    }

    // Gambar posisi bola 'O' dan robot 'R'
    int bRow, bCol, rRow, rCol;
    if (Field::worldToGrid(ball.getPosition(), bRow, bCol)) {
        field.setCell(bRow, bCol, 'O');
    }
    if (Field::worldToGrid(striker.getPosition(), rRow, rCol)) {
        field.setCell(rRow, rCol, 'R');
    }

    // Render grid
    field.display();

    // Uji exception handling
    try {
        striker.act(ball);
    } catch (const RobotException& e) {
        // Exception tertangani dengan aman
    }

    return 0;
}