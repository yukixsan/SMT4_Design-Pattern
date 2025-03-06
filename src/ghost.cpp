#include "Ghost.h"
#include <random>
#include <chrono>

Ghost::Ghost() : x(5), y(5), icon('G'), running(false) {}

Ghost::~Ghost() {
    stopMoving(); // Ensure thread stops before destruction
}

void Ghost::move(int dx, int dy, Map &map) {
    if (map.isWalkable(y + dy, x + dx)) {
        x += dx;
        y += dy;
    }
}

void Ghost::draw() {
    gotoxy(x, y);
    std::cout << icon;
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::moveLoop(Map &map) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int prevX = x, prevY = y;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    while (running) {
        prevX = x; prevY = y;

        int direction = dis(gen);
        switch (direction) {
            case 0: move(0, -1, map); break; // Up
            case 1: move(0, 1, map); break;  // Down
            case 2: move(-1, 0, map); break; // Left
            case 3: move(1, 0, map); break;  // Right
        }

        // Restore the map tile at the previous position
        gotoxy(prevX, prevY);
        std::cout << map.getTile(prevY, prevX);

        gotoxy(x, y);
        std::cout << icon;

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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

void Ghost::gotoxy(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {x, y};
    SetConsoleCursorPosition(hStdout, position);
}