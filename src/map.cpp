#include "Map.h"
#include "utility.h"
#include <cstdio> // For printf

// Initialize the map in the constructor
Map::Map() {
    char temp_map[23][39] = {
        "+####################################+",
        "|                                    |",
        "| #### ##### ###    ### ##### ####   |",
        "| #         #          #         #   |",
        "| # ### ### # ###  ### # ### ### #   |",
        "|                                    |",
        "| ### # ##### ###  ### ##### # ###   |",
        "|     #        #    #        #       |",
        "| ### # ### ###      ### ### # ###   |",
        "| #   #   #            #   #   #     |",
        "| # ### ### ###      ### ### ### #   |",
        "|          #    |  |    #            |",
        "| ### ### ### ##      ### ### ### #  |",
        "| #   #   #            #   #   #     |",
        "| ### # ### ###      ### ### # ### |",
        "|     #        #    #        #     |",
        "| ### # ##### ###  ### ##### # ### |",
        "|                                    |",
        "| # ### ### # ###  ### # ### ### # |",
        "| #         # O        O#         # |",
        "| #### ##### ###    ### ##### #### |",
        "|                                    |",
        "+####################################+"
    };
    // Copy the temporary map to the class variable
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = temp_map[i][j];
        }
    }

    
}

// Function to display the map
void Map::ShowMap(int pacmanX, int pacmanY) {
    system("cls"); // Clear screen

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == pacmanX && y == pacmanY) {
                std::cout << "P"; // Pacman character
            } else {
                std::cout << map[y][x]; // Normal map tile
            }
        }
        std::cout << std::endl;
    }
}
void Map::redrawMap(int pacmanX, int pacmanY) {
    for (int y = 0; y < HEIGHT; y++) {
        gotoxy(0, y); // Move cursor to start of each line
        for (int x = 0; x < WIDTH; x++) {
            if (x == pacmanX && y == pacmanY) {
                std::cout << "P";
            } else {
                std::cout << map[y][x];
            }
        }
    }
}
//Check walkable map
bool Map::isWalkable(int y, int x) 
{
    return (map[y][x] == ' ' || map[y][x] == '.'); 
}

//Return tile
char Map::getTile(int y, int x) {
    return map[y][x]; // Returns character at (x, y)
}
void Map::setTile(int y, int x, char tile) {
    map[y][x] = tile; // Update the map tile
}