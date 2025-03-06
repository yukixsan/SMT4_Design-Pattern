#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
using namespace std;

int main() {
    Map gameMap;
    Pacman pacman(15, 16); // Initial Pacman position
    Ghost ghost; // Default ghost position (5, 5)

    system("cls"); // Clear console
    gameMap.ShowMap(); // Draw the map without Pacman
    pacman.draw(); // Draw Pacman
    ghost.draw();  // Draw ghost

    pacman.startMoving(gameMap); // Start Pacman movement
    ghost.startMoving(gameMap);  // Start ghost movement

    std::cin.get(); // Wait for user input to exit

    pacman.stopMoving(); // Stop Pacman thread
    ghost.stopMoving();  // Stop ghost thread
    return 0;
}