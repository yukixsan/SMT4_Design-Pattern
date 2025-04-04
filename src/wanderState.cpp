#include "WanderState.h"
#include "Ghost.h"
#include "ChaseState.h" // For state transition
#include <cstdlib>
#include <ctime>
#include <cmath> // For distance calculation

WanderState::WanderState() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }
}

void WanderState::update(Ghost& ghost, Map& map, const Pacman& pacman) {
    int currentX = ghost.getX();
    int currentY = ghost.getY();
    int pacmanX = pacman.getX();
    int pacmanY = pacman.getY();

    // Check distance to Pacman
    int dx = pacmanX - currentX;
    int dy = pacmanY - currentY;
    double distance = std::sqrt(dx * dx + dy * dy); // Euclidean distance

    if (distance <= DETECTION_RADIUS) {
        ghost.setState(new ChaseState()); // Transition to ChaseState
        return; // Exit early since state has changed
    }

    // Random movement
    int newX = currentX;
    int newY = currentY;
    int direction = rand() % 4;
    switch (direction) {
        case 0: if (map.isWalkable(currentY - 1, currentX)) newY--; break; // Up
        case 1: if (map.isWalkable(currentY + 1, currentX)) newY++; break; // Down
        case 2: if (map.isWalkable(currentY, currentX - 1)) newX--; break; // Left
        case 3: if (map.isWalkable(currentY, currentX + 1)) newX++; break; // Right
    }

    ghost.setX(newX);
    ghost.setY(newY);
}