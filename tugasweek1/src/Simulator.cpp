#include "Simulator.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

Simulator::Simulator(const Striker& s, const Ball& b, int maxTicks)
    : striker(s), ball(b), tick(0), maxTicks(maxTicks), goalScored(false) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
#endif
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

    // Kembalikan kursor ke posisi awal (1,1) agar output tidak turun/scroll ke bawah
    std::cout << "\033[H";
    std::cout << "Tick: " << tick << " | State: " << striker.getStateName() << "\033[K\n";
    displayField.display();
    std::cout << "\033[K\n" << std::flush;
}

void Simulator::run() {
    // Bersihkan layar sekali di awal simulasi
    std::cout << "\033[2J\033[H" << std::flush;
    render();
    SLEEP_MS(200);

    while (tick < maxTicks && !goalScored) {
        step();
        render();
        SLEEP_MS(200);

        if (goalScored) {
            std::cout << "GOAL!\033[K\n";
            break;
        }
    }
}

bool Simulator::isGoal() const { return goalScored; }
int Simulator::getTick() const { return tick; }
