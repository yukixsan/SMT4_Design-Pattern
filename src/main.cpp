#include <iostream>
#include <windows.h>
#include <thread> // For sleep
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "ChaseState.h" // Include the new state
using namespace std;

int main() {
    Map gameMap;
    Pacman pacman(19, 1);
    Ghost ghost(12, 18, 'G', new WanderState());

    system("cls");
    gameMap.ShowMap(pacman.getX(), pacman.getY());
    pacman.draw();
    ghost.draw();

    pacman.startMoving(gameMap);
    ghost.startMoving(gameMap, pacman);

    std::cin.get();

    pacman.stopMoving();
    ghost.stopMoving();

    return 0;
}