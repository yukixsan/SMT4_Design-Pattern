#ifndef GHOST_FACTORY_H
#define GHOST_FACTORY_H

#include "Ghost.h"
#include "WanderState.h"
#include <cstdlib> // For rand()
#include <ctime>   // For srand()

class GhostFactory {
private:
    static bool seeded;
    static void seedRandom() {
        if (!seeded) {
            srand(static_cast<unsigned>(time(nullptr)));
            seeded = true;
        }
    }

public:
    static Ghost* createRandomGhost(int x) {
        seedRandom();
        char icons[] = {'B', 'P', 'I', 'C'}; // Blinky, Pinky, Inky, Clyde
        int typeIndex = rand() % 4; // Random index: 0-3
        char ghostIcon = icons[typeIndex];
        return new Ghost(x, 11, ghostIcon, new WanderState(ghostIcon));
    }
};

#endif