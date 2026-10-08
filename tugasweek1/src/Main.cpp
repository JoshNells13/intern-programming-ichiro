#include "Simulator.hpp"
#include <iostream>

int main() {
    double rx, ry, rTheta;
    double bx, by;

    std::cout << "Masukkan posisi Robot (x y): ";
    std::cin >> rx >> ry;

    std::cout << "Masukkan sudut hadap Robot (derajat): ";
    std::cin >> rTheta;

    std::cout << "Masukkan posisi Bola (x y): ";
    std::cin >> bx >> by;
    std::cout << "\n";

    Striker striker(rx, ry, rTheta);
    Ball ball(bx, by);

    Simulator sim(striker, ball, 30);
    sim.run();

    return 0;
}