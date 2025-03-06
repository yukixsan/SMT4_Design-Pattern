#include "Ghost.h"
#include <chrono>

Ghost::Ghost(int startX, int startY, char ghostIcon, MovementStrategy* movementStrategy)
    : x(startX), y(startY), icon(ghostIcon), running(false), strategy(movementStrategy) {}

Ghost::~Ghost() {
    stopMoving(); // Ensure thread is stopped before destruction
    delete strategy; //clean up strategy
}

void Ghost::draw() {
    gotoxy(x, y);
    std::cout << icon; // Draw ghost character
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::moveLoop(Map &map, const Pacman& pacman) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Hide cursor

    int prevX = x, prevY = y; // Store previous position
    while (running) {
        prevX = x; prevY = y;

        // Use the strategy to move
        strategy->move(x, y, map, pacman);

        // Erase previous position
        gotoxy(prevX, prevY);
        std::cout << " ";

        // Draw new position
        gotoxy(x, y);
        std::cout << icon;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Ghost::startMoving(Map &map, const Pacman& pacman) {
    running = true;
    movementThread = std::thread([this, &map, &pacman]() {
        this->moveLoop(map, pacman);
    });
}

void Ghost::stopMoving() {
    running = false;
    if (movementThread.joinable()) {
        movementThread.join();
    }
}