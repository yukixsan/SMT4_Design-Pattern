// ColoredGhostDecorator.h
#ifndef COLORED_GHOST_DECORATOR_H
#define COLORED_GHOST_DECORATOR_H

#include "ghostInterface.h"
#include "Ghost.h"
#include <windows.h>

class ColoredGhostDecorator : public ghostInterface {
private:
    Ghost* wrappedGhost;
    WORD color;

public:
    ColoredGhostDecorator(Ghost* ghost, WORD consoleColor)
        : wrappedGhost(ghost), color(consoleColor) {}

    ~ColoredGhostDecorator() {
        delete wrappedGhost; // Clean up original ghost
    }

    void draw() override {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;

        // Save current color
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;

        // Set new color and draw
        SetConsoleTextAttribute(hConsole, color);
        wrappedGhost->draw();
        SetConsoleTextAttribute(hConsole, saved_attributes); // Restore
    }

    void startMoving(Map &map, const Pacman& pacman) override {
        wrappedGhost->startMoving(map, pacman);
    }

    void stopMoving() override {
        wrappedGhost->stopMoving();
    }

    int getX() const override {
        return wrappedGhost->getX();
    }

    int getY() const override {
        return wrappedGhost->getY();
    }
};

#endif
