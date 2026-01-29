#ifndef SNAKE_H
#define SNAKE_H
#include "segment.h"
#include "Food.h"
#include <vector>
#include <conio.h>
#include <windows.h>

enum Direction
{
    UP, DOWN, LEFT, RIGHT, NONE
};

class Snake
{
private:
    std::vector<segment> body;
    Direction direction;
    Direction newDirection;
    bool collision;
    bool collisionWithWall;

public:
    Snake(int startX=10, int startY=5, int initialLength=3);

    void move();
    void setDirection(Direction newDirect);
    bool valide_collisionWithWall(int width, int height);
    bool truthCollision() const {return collision;};
    void eating(std::vector<Food> &foods, int &count);

    const std::vector<segment>& getBody() const {return body;};
};

#endif