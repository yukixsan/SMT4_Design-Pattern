#include "Ghost.h"
#include <random>
#include <chrono>

Ghost::Ghost(int startX, int startY, char ghostIcon) 
    : x(startX), y(startY), icon(ghostIcon), running(false) {}

Ghost::~Ghost() {
    stopMoving(); // Ensure thread is stopped before destruction
}

void Ghost::move(int dx, int dy, Map &map) {
    char nextTile = map.getTile(y + dy, x + dx);
    if (map.isWalkable(y + dy, x + dx)) { // Check if the next tile is walkable
        x += dx;
        y += dy;
    }
}

void Ghost::draw() {
    gotoxy(x, y);
    std::cout << icon; // Draw ghost character
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::moveLoop(Map &map) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Hide cursor

    int prevX = x, prevY = y; // Store previous position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3); // For random direction

    while (running) {
        prevX = x; prevY = y; // Update previous position

        // Random movement: 0=up, 1=down, 2=left, 3=right
        int direction = dis(gen);
        switch (direction) {
            case 0: move(0, -1, map); break; // Up
            case 1: move(0, 1, map); break;  // Down
            case 2: move(-1, 0, map); break; // Left
            case 3: move(1, 0, map); break;  // Right
        }

        // Erase previous position
        gotoxy(prevX, prevY);
        std::cout << " ";

        // Draw new position
        gotoxy(x, y);
        std::cout << icon;

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Slower than Pacman
    }
}

void Ghost::startMoving(Map &map) {
    running = true;
    movementThread = std::thread(&Ghost::moveLoop, this, std::ref(map));
}

void Ghost::stopMoving() {
    running = false;
    if (movementThread.joinable()) {
        movementThread.join();
    }
}