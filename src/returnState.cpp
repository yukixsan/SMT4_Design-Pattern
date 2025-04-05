#include "ReturnState.h"
#include "Ghost.h"
#include "WanderState.h"

ReturnState::ReturnState() : GhostState('R'), returnStart(std::chrono::steady_clock::now()), firstUpdate(true) {}
void ReturnState::update(Ghost& ghost, Map& map, const Pacman& pacman) {
    // Set position to ghost house only on first update
    if (firstUpdate) {
        ghost.setX(11);
        ghost.setY(18);
        firstUpdate = false;
    }

    // Check if 2 seconds have passed
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - returnStart).count();

    if (elapsed >= 2000) { // 2000ms = 2 seconds
        ghost.setState(new WanderState(ghost.getIcon()));
    }
}