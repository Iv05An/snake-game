#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <windows.h>
#include "Food.h"
#include "Snake.h"
#include "Record.h"
#include "Menu.h"
#include "Utils.h"
#include "segment.h"

using namespace std;

class Game
{
private:
    gameState currentState;
    int width, height;
    Snake Snake;
    vector<segment> SnakeBody;
    // vector<segment> SnakeBody;
    vector<Food> foods;
    bool this_snake;
    int size;
    bool gameover;
    int count;
public:
    Game(int width, int height);
    void Run();
private:
    int gameLoop(gameState &currentState);
};




#endif