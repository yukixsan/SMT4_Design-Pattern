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

    if (nextTile == ' ' || nextTile == '.' || nextTile == 'O') {  // Walkable spaces
        x += dx;
        y += dy;

        if (nextTile == 'O') {
            poweredUp = true;
            powerUpEnd = std::chrono::steady_clock::now() + std::chrono::seconds(5); // 5-second power-up
            map.setTile(y, x, ' '); // Remove the power pellet
        }
        //if (nextTile == '.') { points++; } // Increase score if eating a dot
    }
}

void Pacman::draw() {
    gotoxy(x, y);
    std::cout << (poweredUp ? "@" : "P"); // @ for powered-up, P for normal
}
bool Pacman::isPoweredUp() const {
    if (poweredUp) {
        // Check if power-up has expired
        auto now = std::chrono::steady_clock::now();
        if (now >= powerUpEnd) {
            const_cast<Pacman*>(this)->poweredUp = false; // Hack to update in const method
            return false;
        }
        return true;
    }
    return false;
}
int Pacman::getX() const { return x; }
int Pacman::getY() const { return y; }
int Pacman::getPoints() const { return points; }

void Pacman::moveLoop(Map &map) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int prevX = x, prevY = y;

    while (running) {
        prevX = x; prevY = y;

        if (GetAsyncKeyState(VK_UP)) move(0, -1, map);
        if (GetAsyncKeyState(VK_DOWN)) move(0, 1, map);
        if (GetAsyncKeyState(VK_LEFT)) move(-1, 0, map);
        if (GetAsyncKeyState(VK_RIGHT)) move(1, 0, map);

        // Erase previous position with the map's tile
        gotoxy(prevX, prevY);
        std::cout << map.getTile(prevY, prevX); // Restore original tile

        gotoxy(x, y);
        std::cout << (poweredUp ? "@" : "P");
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
