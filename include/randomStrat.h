#ifndef RANDOM_STRATEGY_H
#define RANDOM_STRATEGY_H

#include "MovementStrategy.h"
#include <random>

class RandomStrategy : public MovementStrategy {
private:
    std::random_device rd;
    std::mt19937 gen; //Random number generation
    std::uniform_int_distribution<> dis; //distribution
    //generated once on the strategy for efficiency bruh

public:
    RandomStrategy();
    void move(int& x, int& y, Map& map, const Pacman& pacman) override;
};

#endif