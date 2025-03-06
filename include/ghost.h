#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include <windows.h>
#include <thread>
#include <atomic>

class Ghost {
public:
    int x, y;  // Ghost position
    char icon; // Character representing the ghost (e.g., 'G')

    Ghost(); // Constructor
    ~Ghost(); // Destructor to clean up thread

    void startMoving(Map &map); // Start ghost movement
    void stopMoving(); // Stop ghost movement
    void move(int dx, int dy, Map &map); // Move ghost in a direction
    void draw(); // Draw ghost on console
    int getX() const; // Get X position
    int getY() const; // Get Y position

private:
    std::atomic<bool> running; // Control ghost movement thread
    std::thread movementThread; // Thread for ghost movement

    void gotoxy(short x, short y);
    void moveLoop(Map &map); // Ghost movement logic
};

#endif