#include "Simulator.hpp"
#include "ConfigLoader.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  double rx, ry, rTheta;
  double bx, by;
  int maxTicks = 50;

  bool fromConfig = false;

  // Cara 1: Cek jika argumen file diberikan di terminal (misal: main.exe config.txt)
  if (argc > 1) {
    fromConfig = true;
  } else {
    // Cara 2: Tanyakan opsi input kepada pengguna
    std::cout << "Pilih Sumber Konfigurasi:\n";
    std::cout << "  [1] Muat dari file (config.txt)\n";
    std::cout << "  [2] Input manual koordinat\n";
    std::cout << "Pilihan [1/2] (default 2): ";
    int choice = 2;
    if (std::cin >> choice && choice == 1) {
      fromConfig = true;
    }
  }

  if (fromConfig) {
    std::string configFile = (argc > 1) ? argv[1] : "config.txt";
    std::cout << "\n[INFO] Memuat konfigurasi dari: " << configFile << "\n";
    SimConfig cfg = ConfigLoader::loadFromFile(configFile);
    rx = cfg.robotX;
    ry = cfg.robotY;
    rTheta = cfg.robotOrientation;
    bx = cfg.ballX;
    by = cfg.ballY;
    maxTicks = cfg.maxTicks;
    std::cout << "  - Posisi Robot : (" << rx << ", " << ry << "), Hadap: " << rTheta << " deg\n";
    std::cout << "  - Posisi Bola  : (" << bx << ", " << by << ")\n";
    std::cout << "  - Max Ticks    : " << maxTicks << "\n\n";
  } else {
    std::cout << "Masukkan posisi Robot (x y) [-4.5 s/d 4.5, -3.0 s/d 3.0]: ";
    std::cin >> rx >> ry;

    std::cout << "Masukkan sudut hadap Robot (derajat) [0, 90, 180, 270]: ";
    std::cin >> rTheta;

    std::cout << "Masukkan posisi Bola (x y)  [-4.5 s/d 4.5, -3.0 s/d 3.0]: ";
    std::cin >> bx >> by;
  }

  Striker striker(rx, ry, rTheta);
  Ball ball(bx, by);

  Simulator sim(striker, ball, maxTicks);
  sim.run();

  return 0;
}