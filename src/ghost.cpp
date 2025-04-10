#include "Ghost.h"
#include "frightenedState.h"

#include <chrono>

Ghost::Ghost(int startX, int startY, char ghostIcon, GhostState* initialState)
    : x(startX), y(startY), icon(ghostIcon), running(false), currentState(initialState) {}

Ghost::~Ghost() {
    stopMoving();
    delete currentState;
}

void Ghost::draw() {
}
int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::moveLoop(Map& map, const Pacman& pacman) {
    

    int prevX = x, prevY = y;
    while (running) {
        prevX = x; prevY = y;

        if (dynamic_cast<FrightenedState*>(currentState) != nullptr &&
            x == pacman.getX() && y == pacman.getY()) {
            setState(new ReturnState());
        }

        if (dynamic_cast<ReturnState*>(currentState) == nullptr) {
            if (pacman.isPoweredUp() && dynamic_cast<FrightenedState*>(currentState) == nullptr &&
                dynamic_cast<ColoredFrightenedState*>(currentState) == nullptr) { // Check for decorator too
                setState(new ColoredFrightenedState(new FrightenedState()));
            } else if (!pacman.isPoweredUp() && 
                       dynamic_cast<WanderState*>(currentState) == nullptr && 
                       dynamic_cast<ChaseState*>(currentState) == nullptr) {
                setState(new WanderState(icon));
            }
        }

        currentState->update(*this, map, pacman);

        gotoxy(prevX, prevY);
        std::cout << map.getTile(prevY, prevX);

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