#include "Map.h"
#include "utility.h" // For gotoxy
#include "Ghost.h"
#include "ghostState.h"
#include <iostream>

const char* Map::mapData[HEIGHT] = {
    "|-------------------------------------|", // 0: Border (0 obstacles)
    "|      #     #     #     #     #     #|", // 1: 6 obstacles
    "|                                     |", // 2: Open
    "|                                     |", // 3: Open
    "|   #        #        #        #      |", // 4: 4 obstacles
    "|                                     |", // 5: Open
    "|     ##     #    ##    ##     #     #|", // 6: 6 obstacles
    "|                                     |", // 7: Open
    "|                       O             |", // 8: Open
    "|                                     |", // 9: Open
    "|   #       O#        #        #      |", // 10: 4 obstacles
    "|                                     |", // 11: Open
    "|      #     #     #     #     #     #|", // 12: 6 obstacles
    "|                                     |", // 13: Open
    "|                                     |", // 14: Open
    "|                                     |", // 15: Open
    "|   #       O#        #       O#      |", // 16: 4 obstacles
    "|                                     |", // 17: Open
    "|#     #     #     #     #     #     #|", // 18: 6 obstacles
    "|                                     |", // 19: Open
    "|                                     |", // 20: Open
    "|#     #     #     #     #     #     #|", // 21: 6 obstacles
    "|-------------------------------------|", // 22: Border (0 obstacles)
};

Map::Map() {
    std::cout << "Map constructor started\n";
    for (int y = 0; y < HEIGHT; y++) {
        if (strlen(mapData[y]) != WIDTH) {
            std::cout << "Row " << y << " has length " << strlen(mapData[y]) << ", expected " << WIDTH << "\n";
            return;
        }
        for (int x = 0; x < WIDTH; x++) {
            map[y][x] = mapData[y][x];
        }
    }  
    std::cout << "Map constructor filled\n";
    initializeBuffer();
    std::cout << "Map constructor finished\n";
}

void Map::initializeBuffer() {
    buffer.clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            buffer += map[y][x];
        }
        buffer += '\n';
    }
}

void Map::updateBuffer(int pacmanX, int pacmanY, const std::vector<Ghost*>& ghosts) {
    // Start with the base map
    initializeBuffer();

    // Convert buffer to a modifiable 2D-like structure
    std::string newBuffer = buffer;
    int index;

    // Place Pacman
    index = pacmanY * (WIDTH + 1) + pacmanX; // +1 for newline
    if (index >= 0 && index < newBuffer.size()) {
        newBuffer[index] = 'P';
    }

    // Place ghosts
    for (const auto* ghost : ghosts) {
        int gx = ghost->getX();
        int gy = ghost->getY();
        index = gy * (WIDTH + 1) + gx;
        if (index >= 0 && index < newBuffer.size()) {
            newBuffer[index] = ghost->getStateIcon();
        }
    }

    buffer = newBuffer;
}

void Map::redrawMap() {
    system("cls"); // Clear screen
    std::cout << buffer; // Draw the buffered map
}

bool Map::isWalkable(int y, int x) {
    return (map[y][x] == ' ' || map[y][x] == '.' || map[y][x] == 'O' || map[y][x] == '|' || map[y][x] == '-');
}

char Map::getTile(int y, int x) {
    return map[y][x];
}

void Map::setTile(int y, int x, char tile) {
    map[y][x] = tile;
}