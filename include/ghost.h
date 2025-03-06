#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include <windows.h>
#include <thread>
#include <atomic>

class Ghost {
private:
    int x, y;          // Ghost position
    char icon;         // Character representing the ghost (e.g., 'G')
    std::atomic<bool> running; // Control ghost movement thread
    std::thread movementThread; // Thread for ghost movement

    void gotoxy(short x, short y) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD position = {x, y};
        SetConsoleCursorPosition(hStdout, position);
    }

    void moveLoop(Map &map); // Ghost movement logic

public:
    Ghost(int startX, int startY, char ghostIcon = 'G'); // Constructor
    ~Ghost(); // Destructor to clean up thread

    void startMoving(Map &map); // Start ghost movement
    void stopMoving(); // Stop ghost movement
    void move(int dx, int dy, Map &map); // Move ghost in a direction
    void draw(); // Draw ghost on console
    int getX() const; // Get X position
    int getY() const; // Get Y position
};

#endif