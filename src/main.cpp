#include <iostream>
#include <windows.h>
#include <vector>
#include <limits>
#include <thread>
#include <atomic>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostFactory.h"
using namespace std;

void redrawThread(Map& map, const Pacman& pacman, const vector<Ghost*>& ghosts, atomic<bool>& running) {
    cout << "Redraw thread started\n";
    while (running) {
        map.updateBuffer(pacman.getX(), pacman.getY(), ghosts);
        map.redrawMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    cout << "Redraw thread stopped\n";
}

int main() {


    cout << "Program starting\n";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = false;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    cout << "Cursor hidden\n";

    Map gameMap;
    Pacman pacman(19, 1);
    vector<Ghost*> ghosts;
    atomic<bool> running(true);

    int difficulty;
    cout << "Enter difficulty (1-4): ";
    cin >> difficulty;
    cout << "Difficulty entered: " << difficulty << "\n";

    int ghostCount;
    switch (difficulty) {
        case 1: ghostCount = 1; break;
        case 2: ghostCount = 2; break;
        case 3: ghostCount = 3; break;
        case 4: ghostCount = 4; break;
        default:
            cout << "Invalid difficulty, defaulting to 1\n";
            ghostCount = 1;
            difficulty = 1;
            break;
    }
    cout << "Ghost count: " << ghostCount << "\n";

    int startX = 16;
    for (int i = 0; i < ghostCount; i++) {
        int spawnX = startX + (i * difficulty);
        ghosts.push_back(GhostFactory::createRandomGhost(spawnX));
        cout << "Ghost " << i + 1 << " spawned at (" << spawnX << ", 11) with icon " << ghosts[i]->getStateIcon() << "\n";
    }

    cout << "Updating buffer\n";
    gameMap.updateBuffer(pacman.getX(), pacman.getY(), ghosts);
    cout << "Buffer updated, drawing map\n";
    gameMap.redrawMap();
    cout << "Initial map drawn\n";

    // Pause to inspect
    cout << "Press enter to start game\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    pacman.startMoving(gameMap);
    for (auto* ghost : ghosts) {
        ghost->startMoving(gameMap, pacman);
    }
    thread redraw(redrawThread, ref(gameMap), ref(pacman), ref(ghosts), ref(running));

    cout << "Game running, press enter to exit\n";
    cin.get();

    running = false;
    pacman.stopMoving();
    for (auto* ghost : ghosts) {
        ghost->stopMoving();
        delete ghost;
    }
    if (redraw.joinable()) {
        redraw.join();
    }
    cout << "Program exiting\n";

    return 0;
}