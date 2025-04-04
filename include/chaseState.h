#ifndef CHASE_STATE_H
#define CHASE_STATE_H

#include "GhostState.h"

class ChaseState : public GhostState {
public:
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
    char getIcon() const override { return 'G'; }
};

#endif // CHASE_STATE_H