#include "FrightenedState.h"
#include "Ghost.h"
#include <cstdlib>
#include <ctime>

// Remove the constructor definition here
// FrightenedState::FrightenedState() : GhostState('F') { ... } <- Delete this
FrightenedState::FrightenedState() : GhostState('F') {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
}
void FrightenedState::update(Ghost& ghost, Map& map, const Pacman& pacman) {
    

    int currentX = ghost.getX();
    int currentY = ghost.getY();
    int newX = currentX;
    int newY = currentY;

    int direction = rand() % 4;
    switch (direction) {
        case 0: if (map.isWalkable(currentY - 1, currentX)) newY--; break;
        case 1: if (map.isWalkable(currentY + 1, currentX)) newY++; break;
        case 2: if (map.isWalkable(currentY, currentX - 1)) newX--; break;
        case 3: if (map.isWalkable(currentY, currentX + 1)) newX++; break;
    }

    ghost.setX(newX);
    ghost.setY(newY);
}