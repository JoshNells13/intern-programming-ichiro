#include "Simulator.hpp"
#include <iostream>

Simulator::Simulator(const Striker& s, const Ball& b, int maxTicks)
    : striker(s), ball(b), tick(0), maxTicks(maxTicks), goalScored(false) {
    striker.sense(ball);
}

void Simulator::step() {
    tick++;

    // 1. SENSE
    striker.sense(ball);

    // 2. THINK
    striker.think();

    // 3. ACT
    try {
        striker.act(ball);
    } catch (const RobotException& e) {
    }

    // 4. UPDATE BALL
    ball.update();

    // 5. UPDATE SENSOR SETELAH AKSI
    striker.sense(ball);

    // 6. CEK GOL
    if (Field::isGoal(ball.getPosition())) {
        goalScored = true;
    }
}

void Simulator::render() const {
    Field displayField;

    // Gambar sensor kamera '@'
    const auto& vision = striker.getCurrentVisionArea();
    for (const auto& c : vision) {
        displayField.setCell(c.row, c.col, '@');
    }

    // Gambar bola 'O'
    int bRow, bCol;
    if (Field::worldToGrid(ball.getPosition(), bRow, bCol)) {
        displayField.setCell(bRow, bCol, 'O');
    }

    // Gambar robot 'R'
    int rRow, rCol;
    if (Field::worldToGrid(striker.getPosition(), rRow, rCol)) {
        displayField.setCell(rRow, rCol, 'R');
    }

    std::cout << "Tick: " << tick << " | State: " << striker.getStateName() << "\n";
    displayField.display();
    std::cout << "\n";
}

void Simulator::run() {
    render();

    while (tick < maxTicks && !goalScored) {
        step();
        render();

        if (goalScored) {
            std::cout << "GOAL!\n";
            break;
        }
    }
}

bool Simulator::isGoal() const { return goalScored; }
int Simulator::getTick() const { return tick; }
