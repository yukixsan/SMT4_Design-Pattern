#ifndef FRIGHTENED_STATE_H
#define FRIGHTENED_STATE_H

#include "GhostState.h"

class FrightenedState : public GhostState {
public:
FrightenedState();
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
    char getIcon() const override { return 'F'; }
};

#endif