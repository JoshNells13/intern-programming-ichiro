#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Field.hpp"
#include "Ball.hpp"
#include "Striker.hpp"

class Simulator {
private:
    Field field;
    Ball ball;
    Striker striker;
    int tick;
    int maxTicks;
    bool goalScored;

public:
    Simulator(const Striker& s, const Ball& b, int maxTicks = 30);

    void step();
    void run();
    void render() const;

    bool isGoal() const;
    int getTick() const;
};

#endif
