#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "Map.h"
#include "Pacman.h"

class MovementStrategy {
public:
    virtual void move(int& x, int& y, Map& map, const Pacman& pacman) = 0;
    virtual ~MovementStrategy() = default;
};

#endif