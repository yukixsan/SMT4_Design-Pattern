#include "Map.h"
#include <cstdio>

Map::Map() {
    char temp_map[HEIGHT][WIDTH] = {
        "+#############################+",
        "|                             |",
        "|                             |",
        "|## ########### ##   #########|",
        "|                             |",
        "| | |### |  |           |     |",
        "| |      |  | |###  |   |  |  |",
        "| | #####|  | |      ## |     |",
        "| |           |###  |      |  |",
        "| |##### ###         ##       |",
        "|          ######  ####### ###|",
        "|                             |",
        "|#### ####             #######|",
        "|                             |",
        "|                             |",
        "|                             |",
        "+#############################+"};

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = temp_map[i][j];
        }
    }
}

void Map::ShowMap() {
    system("cls"); // Clear screen

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << map[y][x]; // Draw only the map tiles
        }
        std::cout << std::endl;
    }
}

bool Map::isWalkable(int y, int x) {
    return (map[y][x] == ' ' || map[y][x] == '.');
}

char Map::getTile(int y, int x) {
    return map[y][x];
}   