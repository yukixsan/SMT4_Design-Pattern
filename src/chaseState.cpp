#include "ChaseState.h"
#include "Ghost.h"
#include "Pacman.h" // Needed for pacman.getX() and getY()

void ChaseState::update(Ghost& ghost, Map& map, const Pacman& pacman) {
    int currentX = ghost.getX();
    int currentY = ghost.getY();
    int pacmanX = pacman.getX();
    int pacmanY = pacman.getY();

    int newX = currentX;
    int newY = currentY;

    // Simple chase: prioritize horizontal then vertical movement
    if (pacmanX > currentX && map.isWalkable(currentY, currentX + 1)) {
        newX++;
    } else if (pacmanX < currentX && map.isWalkable(currentY, currentX - 1)) {
        newX--;
    } else if (pacmanY > currentY && map.isWalkable(currentY + 1, currentX)) {
        newY++;
    } else if (pacmanY < currentY && map.isWalkable(currentY - 1, currentX)) {
        newY--;
    }

    ghost.setX(newX);
    ghost.setY(newY);
}