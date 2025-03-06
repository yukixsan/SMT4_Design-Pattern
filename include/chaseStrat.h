#ifndef CHASE_STRATEGY_H
#define CHASE_STRATEGY_H

#include "movementStrategy.h"

class ChaseStrategy : public MovementStrategy {
public:
    void move(int& x, int& y, Map& map, const Pacman& pacman) override;
};

#endif