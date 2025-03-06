#include "Ghost.h"
#include <iostream>
#include <random>
#include <chrono>

// MovementStrategy interface
class MovementStrategy {
public:
    virtual ~MovementStrategy() = default; // Virtual destructor for polymorphism
    virtual void moveGhost(int& x, int& y, Map& map) = 0; // Pure virtual method
};

// RandomMovement strategy
class RandomMovement : public MovementStrategy {
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

public:
    RandomMovement() : gen(rd()), dis(0, 3) {}
    void moveGhost(int& x, int& y, Map& map) override {
        int dx = 0, dy = 0;
        int direction = dis(gen);
        switch (direction) {
            case 0: dy = -1; break; // Up
            case 1: dy = 1; break;  // Down
            case 2: dx = -1; break; // Left
            case 3: dx = 1; break;  // Right
        }
        char nextTile = map.getTile(y + dy, x + dx);
        if (map.isWalkable(y + dy, x + dx)) {
            x += dx;
            y += dy;
        }
    }
};

// ChaseMovement strategy
class ChaseMovement : public MovementStrategy {
private:
    int targetX, targetY; // Target position (e.g., Pacman's position)

public:
    ChaseMovement(int targetX, int targetY) : targetX(targetX), targetY(targetY) {}
    void moveGhost(int& x, int& y, Map& map) override {
        int dx = 0, dy = 0;
        // Simple chase: move toward target
        if (x < targetX) dx = 1; // Move right
        else if (x > targetX) dx = -1; // Move left
        if (y < targetY) dy = 1; // Move down
        else if (y > targetY) dy = -1; // Move up

        char nextTile = map.getTile(y + dy, x + dx);
        if (map.isWalkable(y + dy, x + dx)) {
            x += dx;
            y += dy;
        }
    }

    void setTarget(int newX, int newY) {
        targetX = newX;
        targetY = newY;
    }
};

// GhostFactory interface
class GhostFactory {
public:
    virtual ~GhostFactory() = default;
    virtual Ghost* createGhost(int x, int y, char icon, MovementStrategy* strategy) = 0;
};

// DefaultGhostFactory implementation
class DefaultGhostFactory : public GhostFactory {
public:
    Ghost* createGhost(int x, int y, char icon, MovementStrategy* strategy) override {
        return new Ghost(x, y, icon, strategy ? strategy : new RandomMovement());
    }
};

// Ghost class implementation
Ghost::Ghost(int startX, int startY, char ghostIcon, MovementStrategy* strategy)
    : x(startX), y(startY), icon(ghostIcon), running(false), movementStrategy(strategy) {
    if (!movementStrategy) {
        movementStrategy = new RandomMovement(); // Default strategy
    }
}

Ghost::~Ghost() {
    stopMoving();
    delete movementStrategy; // Clean up strategy
}

void Ghost::moveLoop(Map& map) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo); // Hide cursor

    int prevX = x, prevY = y; // Store previous position

    while (running) {
        prevX = x; prevY = y; // Update previous position

        // Use the movement strategy
        movementStrategy->moveGhost(x, y, map);

        // Erase previous position
        gotoxy(prevX, prevY);
        std::cout << " ";

        // Draw new position
        draw();

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Adjust speed
    }
}

void Ghost::startMoving(Map& map) {
    running = true;
    movementThread = std::thread(&Ghost::moveLoop, this, std::ref(map));
}

void Ghost::stopMoving() {
    running = false;
    if (movementThread.joinable()) {
        movementThread.join();
    }
}

void Ghost::draw() {
    gotoxy(x, y);
    std::cout << icon; // Draw ghost character
}

int Ghost::getX() const { return x; }
int Ghost::getY() const { return y; }

void Ghost::setMovementStrategy(MovementStrategy* strategy) {
    if (strategy != movementStrategy) {
        delete movementStrategy; // Clean up old strategy
        movementStrategy = strategy;
    }
}

MovementStrategy* Ghost::getMovementStrategy() const {
    return movementStrategy;
}