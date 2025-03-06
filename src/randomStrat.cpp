#include "randomStrat.h"

RandomStrategy::RandomStrategy() : gen(rd()), dis(0, 3) {}

void RandomStrategy::move(int& x, int& y, Map& map, const Pacman& pacman) {
    int direction = dis(gen); // Random direction: 0=up, 1=down, 2=left, 3=right
    int dx = 0, dy = 0;
    switch (direction) {
        case 0: dx = 0; dy = -1; break; // Up
        case 1: dx = 0; dy = 1; break;  // Down
        case 2: dx = -1; dy = 0; break; // Left
        case 3: dx = 1; dy = 0; break;  // Right
    }
    if (map.isWalkable(y + dy, x + dx)) {
        x += dx;
        y += dy;
    }
}