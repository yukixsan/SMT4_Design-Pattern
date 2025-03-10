#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "chaseStrat.h"
#include "randomStrat.h"
using namespace std;

int main() {
    Map gameMap;
    Pacman pacman(15, 16); // Initial Pacman position
    Ghost ghost(5,5,'C', new ChaseStrategy());

    system("cls"); // Clear console
    gameMap.ShowMap(pacman.getX(), pacman.getY()); // Initial draw
    pacman.draw();
    ghost.draw();

    pacman.startMoving(gameMap); // Start Pacman movement
    ghost.startMoving(gameMap, pacman);  // Start Ghost movement

    std::cin.get(); // Wait for user input to exit

    pacman.stopMoving(); // Stop Pacman thread
    ghost.stopMoving();  // Stop Ghost thread
    return 0;
}