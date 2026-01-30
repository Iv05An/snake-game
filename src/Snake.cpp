#include "../include/Snake.h"
#include <iostream>

Snake::Snake(int startX, int startY, int initialLength)
{
    direction = RIGHT;
    newDirection = RIGHT;
    collision = false;
    collisionWithWall = false;

    for(int i=0; i<initialLength; ++i)
    {
        segment partBody;
        partBody.x=startX-i;
        partBody.y=startY;

        body.push_back(partBody);
    }
}

void Snake::eating(std::vector<Food> &foods, int &count)
    {
                    // для поедания
        segment tail= body.back();
        for (int i = 0; i<foods.size(); ++i)
        {
            if (body[0].x==foods[i].getX() && body[0].y==foods[i].getY())
            {
                body.push_back({tail.x, tail.y});

                foods.erase(foods.begin()+i);
                count--;
                --i;
                break;
            }
        }
        
    }

void Snake::setDirection(Direction newDirect)
{
    if ((direction==UP && newDirect!=DOWN)||
        (direction==DOWN && newDirect!=UP)||
        (direction==LEFT && newDirect!=RIGHT)||
        (direction==RIGHT && newDirect!=LEFT))
        {
            newDirection=newDirect;
        }
}

bool Snake::valide_collisionWithWall(int width, int height)
{
    if (body.empty()) return false;
    
    // Предсказываем следующую позицию головы
    int nextX = body[0].x;
    int nextY = body[0].y;
    
    // Используем newDirection (будущее направление), а не direction (текущее)
    switch (newDirection)
    {
    case UP:    nextY--; break;
    case DOWN:  nextY++; break;
    case LEFT:  nextX--; break;
    case RIGHT: nextX++; break;
    default: return false; // Если направление не задано
    }
    
    // Проверяем границы (от 0 до width-1, от 0 до height-1)
    // Границы отрисовываются как '#' по индексам 0 и width-1/height-1
    bool inside = (nextX >= 1 && nextX <= width-2 && 
                   nextY >= 1 && nextY <= height-2);
    
    return inside;
}

void Snake::move()
{
    // Обновляем направление
    direction = newDirection;
    
    // Проверяем, можно ли двигаться в этом направлении
    if (direction == NONE) return;
    
    // 1. Вычисляем новую позицию головы
    int newHeadX = body[0].x;
    int newHeadY = body[0].y;
    
    switch (direction)
    {
    case UP:    newHeadY--; break;
    case DOWN:  newHeadY++; break;
    case LEFT:  newHeadX--; break;
    case RIGHT: newHeadX++; break;
    default: break;
    }
                
    // 2. Проверяем столкновение с телом
    collision = false;
    for (int i = 1; i < body.size(); i++) {
        if (body[i].x == newHeadX && body[i].y == newHeadY) {
            collision = true;
            break;
        }    
    }
                
    // 3. Если столкновения нет — двигаем
    if (!collision) {               
        for (int i = body.size()-1; i>0; i--)
        {
            body[i].x = body[i-1].x;
            body[i].y = body[i-1].y;
        }
        
        body[0].x = newHeadX;
        body[0].y = newHeadY;
    }
    // ВАЖНО: Нужно где-то обрабатывать collision = true!
}