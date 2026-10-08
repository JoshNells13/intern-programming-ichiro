#include "Vector2D.h"
#include "Ball.h"
#include "Field.h"
#include <iostream>

int main() {
    std::cout << "=== TAHAP 1: Core Architecture, Math & Basic Entities ===" << std::endl;

    Field field;
    Ball ball(0.0, 0.0);
    Vector2D robotPos(-2.0, 0.0);

    int rRow, rCol, bRow, bCol;
    if (Field::worldToGrid(robotPos, rRow, rCol)) {
        field.setCell(rRow, rCol, 'R');
    }
    if (Field::worldToGrid(ball.getPosition(), bRow, bCol)) {
        field.setCell(bRow, bCol, 'O');
    }

    std::cout << "\nVisualisasi Lapangan Tahap 1:\n";
    field.display();

    std::cout << "\nPengujian Fisika & Vektor:";
    std::cout << "\nJarak Robot ke Bola: " << robotPos.distanceTo(ball.getPosition()) << " m";
    std::cout << "\nSudut Hadap Target: " << (ball.getPosition() - robotPos).angleDeg() << " deg" << std::endl;

    return 0;
}