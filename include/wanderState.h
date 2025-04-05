#ifndef WANDER_STATE_H
#define WANDER_STATE_H

#include "GhostState.h"

class WanderState : public GhostState {
private:
    static const int DETECTION_RADIUS = 5; // Radius to detect Pacman

public:
    WanderState(char ghostIcon); // Use ghost's icon
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
};

#endif