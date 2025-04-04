#ifndef GHOST_STATE_H
#define GHOST_STATE_H

#include "Map.h"
#include "Pacman.h"

class Ghost;

class GhostState {
public:
    virtual ~GhostState() = default; // Virtual destructor for proper cleanup
    virtual void update(Ghost& ghost, Map& map, const Pacman& pacman) = 0; // Core behavior
    virtual char getIcon() const = 0; // Icon might change per state (e.g., frightened ghosts)
};

#endif // GHOST_STATE_H