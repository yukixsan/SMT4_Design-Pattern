#ifndef PACMAN_H
#define PACMAN_H

#include "Map.h"
#include "utility.h"
#include <windows.h>
#include <iostream>
#include <thread>
#include <atomic>

class Pacman {
private:
    int x, y; // Pacman's position
    int points;
    std::atomic<bool> running;
    std::thread movementThread;

    bool poweredUp; // Power up condition
    std::chrono::steady_clock::time_point powerUpEnd; // New: Power-up expiration

    void moveLoop(Map &map);

public:
    Pacman(int startX, int startY);
    ~Pacman();
    void startMoving(Map &map);
    void stopMoving();
    void move(int dx, int dy, Map &map);
    void draw();
    int getX() const;
    int getY() const;
    int getPoints() const;
    bool isPoweredUp() const;
};

#endif