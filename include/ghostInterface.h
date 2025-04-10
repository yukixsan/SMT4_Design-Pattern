// IGhost.h
#ifndef GHOSTINTERFACE_H
#define GHOSTINTERFACE_H

class Map;
class Pacman;
class Ghost;

class ghostInterface {
public:
    virtual ~ghostInterface() {}
    virtual void draw() = 0;
    virtual void startMoving(Map &map, const Pacman& pacman) = 0;
    virtual void stopMoving() = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
};

#endif
