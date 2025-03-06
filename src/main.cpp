#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <chrono>

// Pacman classes
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
using namespace std;

int main() {
    Map gameMap;
    Pacman pacman(15, 16); // Initial Pacman position
    DefaultGhostFactory ghostFactory;
    Ghost* ghost = ghostFactory.createGhost(5, 5, 'G', nullptr); // Create ghost with default RandomMovement
    system("cls"); // Clear console
    gameMap.ShowMap(pacman.getX(), pacman.getY()); // Initial draw
    pacman.draw();
    ghost->draw();

    pacman.startMoving(gameMap); // Start Pacman movement in a separate thread
    ghost->startMoving(gameMap);  // Start Ghost movement in a separate thread

    // Switch to chase strategy after 5 seconds to demonstrate strategy pattern
    std::this_thread::sleep_for(std::chrono::seconds(5));
    ghost->setMovementStrategy(new ChaseMovement(pacman.getX(), pacman.getY()));
    ghost->getMovementStrategy()->setTarget(pacman.getX(), pacman.getY()); // Update target to Pacman's position

    std::cin.get(); // Wait for user input to exit

    pacman.stopMoving(); // Ensure Pacman thread stops before exit
    ghost->stopMoving(); // Ensure Ghost thread stops before exit
    delete ghost; // Clean up dynamically allocated ghost
    return 0;
}