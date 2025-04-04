#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include "pacman.h"
#include "utility.h"
#include "ghostState.h"
#include "chaseState.h"
#include "frightenedState.h"
#include "wanderState.h"
#include <windows.h>
#include <thread>
#include <atomic>
#include <iostream>

class Ghost {
private:
    int x, y;          // Ghost position
    char icon;         // Character representing the ghost (e.g., 'G')
    std::atomic<bool> running; // Control ghost movement thread
    std::thread movementThread; // Thread for ghost movement
    GhostState* currentState;

    void moveLoop(Map &map, const Pacman& pacman); // Ghost movement logic

public:
    Ghost(int startX, int startY, char ghostIcon,  GhostState* initialState); // Constructor
    ~Ghost(); // Destructor to clean up thread

    void startMoving(Map &map, const Pacman& pacman); // Start ghost movement
    void stopMoving(); // Stop ghost movement
    void setState(GhostState* newState); // Set state
    void draw(); // Draw ghost on console
    int getX() const; // Get X position
    int getY() const; // Get Y position

    //Get set X and Y
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

#endif