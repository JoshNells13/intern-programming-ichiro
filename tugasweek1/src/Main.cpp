#include "Simulator.hpp"
#include "ConfigLoader.hpp"

int main() {
    SimConfig cfg = ConfigLoader::loadFromFile("config.txt");

    Striker striker(cfg.robotX, cfg.robotY, cfg.robotOrientation);
    Ball ball(cfg.ballX, cfg.ballY);

    Simulator sim(striker, ball, cfg.maxTicks);
    sim.run();

    return 0;
}