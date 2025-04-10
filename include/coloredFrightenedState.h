#ifndef COLORED_FRIGHTENED_STATE_H
#define COLORED_FRIGHTENED_STATE_H

#include "GhostState.h"
#include "FrightenedState.h"
#include <windows.h>

class ColoredFrightenedState : public GhostState {
private:
    FrightenedState* wrappedState; // The state being decorated
    HANDLE hConsole;

public:
    ColoredFrightenedState(FrightenedState* state);
    ~ColoredFrightenedState();
    void update(Ghost& ghost, Map& map, const Pacman& pacman) override;
    char getIcon() const override;
};

#endif