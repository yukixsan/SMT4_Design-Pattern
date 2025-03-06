#ifndef MAP_H
#define MAP_H

#include <iostream>

#define WIDTH 32   // Map width
#define HEIGHT 18  // Map height

class Map {
public:
    char map[HEIGHT][WIDTH]; // 2D array for the map
    char getTile(int y, int x); // Returns the tile

    Map(); // Constructor
    void ShowMap();  // Function to display the map (no Pacman position)
    bool isWalkable(int y, int x); // Check if it's walkable
};

#endif