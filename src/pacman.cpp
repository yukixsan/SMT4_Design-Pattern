// Pacman.cpp
#include "Pacman.h"
#include <conio.h>
#include <windows.h>

Pacman::Pacman(int startX, int startY) : x(startX), y(startY), points(0), running(false) {}

Pacman::~Pacman() {
    stopMoving();
}

void Pacman::move(int dx, int dy, Map &map) {
    char nextTile = map.getTile(y + dy, x + dx);

    if (nextTile == ' ' || nextTile == '.') {  // Walkable spaces
        x += dx;
        y += dy;
        if (nextTile == '.') { points++; } // Increase score if eating a dot
    }
}

void Pacman::draw() {
    gotoxy(x, y);
    std::cout << "P"; // Pacman character
}

int Pacman::getX() const { return x; }
int Pacman::getY() const { return y; }
int Pacman::getPoints() const { return points; }

void Pacman::moveLoop(Map &map) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Hide cursor to reduce flicker

    int prevX = x, prevY = y; // Store previous position

    while (running) {
        prevX = x; prevY = y; // Update previous position before moving

        if (GetAsyncKeyState(VK_UP)) move(0, -1, map);
        if (GetAsyncKeyState(VK_DOWN)) move(0, 1, map);
        if (GetAsyncKeyState(VK_LEFT)) move(-1, 0, map);
        if (GetAsyncKeyState(VK_RIGHT)) move(1, 0, map);

        // Erase previous position
        gotoxy(prevX, prevY);
        std::cout << " "; 
        
        gotoxy(x, y);  // Move cursor to Pacman’s position
        std::cout << "P"; // Redraw only Pacman

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust speed
    }
}

void Pacman::startMoving(Map &map) {
    running = true;
    movementThread = std::thread(&Pacman::moveLoop, this, std::ref(map));
}

void Pacman::stopMoving() {
    running = false;
    if (movementThread.joinable()) {
        movementThread.join();
    }
}
