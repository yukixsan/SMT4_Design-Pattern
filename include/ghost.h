#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include "pacman.h"
#include "movementStrategy.h"
#include <windows.h>
#include <thread>
#include <atomic>

class Ghost {
private:
    int x, y;          // Ghost position
    char icon;         // Character representing the ghost (e.g., 'G')
    std::atomic<bool> running; // Control ghost movement thread
    std::thread movementThread; // Thread for ghost movement
    MovementStrategy* strategy; //Strategy

    void gotoxy(short x, short y) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD position = {x, y};
        SetConsoleCursorPosition(hStdout, position);
    }

    void moveLoop(Map &map, const Pacman& pacman); // Ghost movement logic

public:
    Ghost(int startX, int startY, char ghostIcon, MovementStrategy* strategy); // Constructor
    ~Ghost(); // Destructor to clean up thread

    void startMoving(Map &map, const Pacman& pacman); // Start ghost movement
    void stopMoving(); // Stop ghost movement
    void move(int dx, int dy, Map &map); // Move ghost in a direction
    void draw(); // Draw ghost on console
    int getX() const; // Get X position
    int getY() const; // Get Y position
};

#endif