#include "Ghost.h"
#include "frightenedState.h"

#include <chrono>

Ghost::Ghost(int startX, int startY, char ghostIcon, GhostState* initialState)
    : x(startX), y(startY), icon(ghostIcon), running(false), currentState(initialState) {}

Ghost::~Ghost() {
    stopMoving(); // Ensure thread is stopped before destruction
    delete currentState; //clean up strategy
}

void Ghost::draw() {
    gotoxy(x, y);
    std::cout << currentState->getIcon(); // Draw ghost character
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::moveLoop(Map& map, const Pacman& pacman) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    int prevX = x, prevY = y;
    while (running) {
        prevX = x; prevY = y;
        // Check if Pacman is powered up and switch state
        if (pacman.isPoweredUp() && dynamic_cast<FrightenedState*>(currentState) == nullptr) {
            setState(new FrightenedState());
        } else if (!pacman.isPoweredUp() && dynamic_cast<ChaseState*>(currentState) == nullptr 
        && dynamic_cast<WanderState*>(currentState) == nullptr)
        {
            setState(new ChaseState());
        }
        currentState->update(*this, map, pacman);

        // Erase previous position with the map's tile
        gotoxy(prevX, prevY);
        std::cout << map.getTile(prevY, prevX); // Restore original tile

        gotoxy(x, y);
        std::cout << currentState->getIcon();

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
void Ghost::setState(GhostState* newState) {
    delete currentState; // Delete old state
    currentState = newState; // Set new state
}