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

Simulator::Simulator(const Striker &s, const Ball &b, int maxTicks)
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
  } catch (const RobotException &e) {
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
  const auto &vision = striker.getCurrentVisionArea();
  for (const auto &c : vision) {
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

  // Kembalikan kursor ke posisi awal (1,1) agar output tidak turun/scroll ke
  // bawah
  std::cout << "\033[H";
  std::cout << " SIMULASI ICHIRO STRIKER Cihuyy \033[K\n";
  std::cout << "Tick: " << tick << "/" << maxTicks
            << " | State: " << striker.getStateName() << "\033[K\n";
  std::cout << "Robot : (" << striker.getPosition().x << ", "
            << striker.getPosition().y << ") hadap " << striker.getOrientation()
            << " deg\033[K\n";
  std::cout << "Bola  : (" << ball.getPosition().x << ", "
            << ball.getPosition().y << ") speed " << ball.getSpeed()
            << " m/tick\033[K\n";
  if (striker.getLastKickType() != "-") {
    std::cout << "Tendang: " << striker.getLastKickType() << "\033[K\n";
  }
  std::cout << "---------------------------------------------------------------"
               "------\033[K\n";
  displayField.display();
  std::cout << "---------------------------------------------------------------"
               "------\033[K\n";
  std::cout << "[Guide Titik Koordinat]:\033[K\n";
  std::cout << "  - Lapangan   : X in [-4.5, 4.5] m, Y in [-3.0, 3.0] m (1 "
               "petak = 0.5m)\033[K\n";
  std::cout
      << "  - Gawang (#) : X in [4.0, 4.5] m,  Y in [-1.5, 1.5] m\033[K\n";
  std::cout << "  - Legenda    : R = Robot | O = Bola | @ = Kamera FOV | # = "
               "Gawang\033[K\n";
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
      std::cout << "                   GOAL! BOLA MASUK KE GAWANG! KRI ALL "
                   "DIVISI IS BACKK            "
                   "         \033[K\n";
      break;
    }
  }

  if (!goalScored) {
    std::cout << "                   Bola tidak masuk ICHIRO Kecewa            "
                 "        \033[K\n";
  }
}

bool Simulator::isGoal() const { return goalScored; }
int Simulator::getTick() const { return tick; }
