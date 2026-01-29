
#include "../include/Food.h"
#include <cstdlib>

Food::Food(int xPos, int yPos): x(xPos), y(yPos) {}

bool Food::isFoodAt(const std::vector<Food> &foods, int checkX, int checkY) //временно как вспомогательная функция
{
    for (const Food &FoodPos: foods)
    {
        if (FoodPos.x==checkX && FoodPos.y==checkY) return true;
        // if (FoodPos.getX()==checkX && FoodPos.getY()==checkY) return true;
    }
    return false;
}

Food Food::generateFood(const std::vector<segment> &snake, const std::vector<Food> &foods, const int& width, const int& height)
{
    int foodX, foodY;
    bool valid = false;
    while (!valid)
    {
        valid = true;
        foodX = 1 + rand() % (width - 2);   // от 1 до width-2
        foodY = 1 + rand() % (height - 2);  // от 1 до height-2
            
        for (int j=0; j<snake.size(); j++)
        {
            if (foodX == snake[j].x && foodY == snake[j].y) 
            {
                valid = false;
                continue;
            }
        }

        if (valid)
        {
            for (const auto &food: foods)
            {
                if (food.x == foodX && food.y == foodY) valid = false;
            }
        }
    }   
    return  Food(foodX, foodY);   
}
