#include "chaseStrat.h"
#include <cstdlib>

void ChaseStrategy::move(int& x, int& y, Map& map, const Pacman& pacman) {
    int pacmanX = pacman.getX();
    int pacmanY = pacman.getY();

    int dx = (pacmanX > x) ? 1 : (pacmanX < x) ? -1 : 0;
    int dy = (pacmanY > y) ? 1 : (pacmanY < y) ? -1 : 0;

    if (std::abs(pacmanX - x) > std::abs(pacmanY - y)) {
        if (map.isWalkable(y, x + dx)) {
            x += dx;
        } else if (map.isWalkable(y + dy, x)) {
            y += dy;
        }
    } else {
        if (map.isWalkable(y + dy, x)) {
            y += dy;
        } else if (map.isWalkable(y, x + dx)) {
            x += dx;
        }
    }
}