// Header file for input output functions
#include <iostream>
#include <stdio.h>
#include <windows.h>  
#include <string>  
#include <vector>  

//pacman classes
#include "map.h"
#include "pacman.h"
using namespace std;

// main() function: where the execution of
// C++ program begins
int main() {  
    Map gameMap;
    Pacman pacman(15, 16); // Initial Pacman position

    system("cls"); // Clear console
    gameMap.ShowMap(pacman.getX(), pacman.getY()); // Initial draw
    pacman.draw();

    pacman.startMoving(gameMap); // Start movement in a separate thread

    std::cin.get(); // Wait for user input to exit

    pacman.stopMoving(); // Ensure thread stops before exit
    return 0;
}