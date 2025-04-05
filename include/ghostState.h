#ifndef GHOST_STATE_H
#define GHOST_STATE_H

#include "Map.h"
#include "Pacman.h"

class Ghost;

class GhostState {
private : 
    char icon;
protected:
    GhostState(char stateIcon) : icon(stateIcon) {} // Protected constructor for derived classes
public:
    virtual ~GhostState() = default; // Virtual destruactor for proper cleanup
    virtual void update(Ghost& ghost, Map& map, const Pacman& pacman) = 0; // Core behavior
     char getIcon() const { return icon; } // New: Access original icon
};

#endif // GHOST_STATE_H