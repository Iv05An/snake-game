#ifndef FOOD_H
#define FOOD_H
#include <vector>
#include "segment.h"

class Food
{
    private:
        int x, y;
    public:
        Food(int xPos, int yPos);

        static bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

        // static Food generateFood(const std::vector<segment> &snake, const std::vector<Food> &foods, const int& width, const int& height);
        static Food generateFood(const std::vector<segment> &snake, const std::vector<Food> &foods, const int& width, const int& height);
        int getX() const {return x;}
        int getY() const {return y;}

};

// bool isFoodAt(const std::vector<Food> &foods, int checkX, int checkY);

#endif