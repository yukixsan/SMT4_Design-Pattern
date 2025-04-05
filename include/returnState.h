#ifndef RETURN_STATE_H
#define RETURN_STATE_H

#include "GhostState.h"
#include <chrono>

class ReturnState : public GhostState {
private:
    std::chrono::steady_clock::time_point returnStart; // Time when ghost returns
    bool firstUpdate; // Flag to set position only once
public:
    ReturnState();
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
};

#endif