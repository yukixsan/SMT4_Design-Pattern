#include "ColoredFrightenedState.h"
#include "Ghost.h"

ColoredFrightenedState::ColoredFrightenedState(FrightenedState* state) 
    : GhostState('F'), wrappedState(state), hConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {
    // Set blue color for frightened state (FOREGROUND_BLUE)
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

ColoredFrightenedState::~ColoredFrightenedState() {
    // Reset to default color (white) on destruction
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    delete wrappedState; // Clean up the wrapped state
}

void ColoredFrightenedState::update(Ghost& ghost, Map& map, const Pacman& pacman) {
    // Delegate update to the wrapped FrightenedState
    wrappedState->update(ghost, map, pacman);
}

char ColoredFrightenedState::getIcon() const {
    return wrappedState->getIcon(); // Use F from FrightenedState
}