#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <vector>


class Pacman;
class Ghost;

class Map {
    private:
    static const int HEIGHT = 23;
    static const int WIDTH = 39;
    static const char* mapData[HEIGHT]; // Static member
    char map[HEIGHT][WIDTH];
    std::string buffer;
public:


    Map();
    void initializeBuffer(); // Build initial buffer
    void updateBuffer(int pacmanX, int pacmanY, const std::vector<Ghost*>& ghosts); // Update with entities
    void redrawMap(); // Draw the buffer to console
    bool isWalkable(int y, int x);
    char getTile(int y, int x);
    void setTile(int y, int x, char tile);
};

#endif
