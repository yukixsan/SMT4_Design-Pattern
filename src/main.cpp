#include <iostream>
#include <windows.h>
#include <vector>
#include <thread> 
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "ghostFactory.h"

using namespace std;


int main() {
    Map gameMap;
    Pacman pacman(19, 1);
    vector<Ghost*> ghosts;
    atomic<bool> running(true);

    // Get difficulty input
    int difficulty;
    cout << "Enter difficulty (1-4): ";
    cin >> difficulty;

    // Set number of ghosts based on difficulty
    int ghostCount;
    switch (difficulty) {
        case 1: ghostCount = 1; break;
        case 2: ghostCount = 2; break;
        case 3: ghostCount = 3; break;
        case 4: ghostCount = 4; break;
        default:
            cout << "Invalid difficulty, defaulting to 1\n";
            ghostCount = 1;
            difficulty = 1; // Normalize for position increment
            break;
    }

    // Spawn ghosts 
    int startX = 16; // Starting column
    for (int i = 0; i < ghostCount; i++) {
        int spawnX = startX + (i * difficulty); // Increment by difficulty
        ghosts.push_back(GhostFactory::createRandomGhost(spawnX));
    }
    //Ghost ghost(12, 18, 'G', new WanderState());

    system("cls");
    gameMap.ShowMap(pacman.getX(), pacman.getY());
    pacman.draw();
    for (auto* ghost : ghosts) {
        ghost->draw();
    }

    pacman.startMoving(gameMap);
    for (auto* ghost : ghosts) {
        ghost->startMoving(gameMap, pacman);
    }


    cin.ignore(1000, '\n'); // Clear buffer
    cin.get(); // Wait for exit

    pacman.stopMoving();
    for (auto* ghost : ghosts) {
        ghost->stopMoving();
        delete ghost;
    }

    return 0;
}