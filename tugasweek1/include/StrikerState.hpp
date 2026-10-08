#ifndef STRIKER_STATE_HPP
#define STRIKER_STATE_HPP

#include <string>

class Striker;
class Ball;

class StrikerState {
public:
    virtual ~StrikerState() = default;
    virtual void handle(Striker& striker, Ball& ball) = 0;
    virtual std::string getName() const = 0;
};

class SearchState : public StrikerState {
public:
    void handle(Striker& striker, Ball& ball) override;
    std::string getName() const override { return "SEARCH_BALL"; }
};

class ApproachState : public StrikerState {
public:
    void handle(Striker& striker, Ball& ball) override;
    std::string getName() const override { return "APPROACH_BALL"; }
};

class AlignState : public StrikerState {
public:
    void handle(Striker& striker, Ball& ball) override;
    std::string getName() const override { return "ALIGN_TO_GOAL"; }
};

class KickState : public StrikerState {
public:
    void handle(Striker& striker, Ball& ball) override;
    std::string getName() const override { return "KICK"; }
};

#endif
