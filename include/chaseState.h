#ifndef CHASE_STATE_H
#define CHASE_STATE_H

#include "GhostState.h"

class ChaseState : public GhostState {
public:
    ChaseState(char ghostIcon) : GhostState(ghostIcon) {} // Use ghost's icon
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
};

#endif // CHASE_STATE_H