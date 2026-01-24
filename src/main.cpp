#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <array>
#include <ctime>
#define N 5

using namespace std;

void clearScreen()
{
    system("clear");
}

struct segment
{
    int x, y;
};

struct food
    {
        int x, y;
    };

food generateFood(vector<food> &foods, const vector<segment> &snake, const int& width, const int& height)
{
    food cordFood;
    bool valid = false;
    while (!valid)
    {
        valid = true;
        cordFood.x = 1 + rand() % (width - 2);   // от 1 до width-2
        cordFood.y = 1 + rand() % (height - 2);  // от 1 до height-2
            
        for (int j=0; j<snake.size(); j++)
        {
            if (cordFood.x == snake[j].x && cordFood.y == snake[j].y) 
            {
                valid = false;
                continue;
            }
        }

        if (valid)
        {
            for (const auto &food: foods)
            {
                if (food.x == cordFood.x && food.y == cordFood.y) valid = false;
            }
        }
    }   
    return  cordFood;              
}

void eating(vector<food> &foods, segment &tail, vector<segment> &snake, int &size, int &count)
{
    for (int i = 0; i<foods.size(); ++i)
    {
        if (snake[0].x==foods[i].x && snake[0].y==foods[i].y)
        {
            snake.push_back({tail.x, tail.y});
            size++;

            foods.erase(foods.begin()+i);
            count--;
            --i;
            break;
        }
    }
    
}

bool isFoodAt(vector<food> &foods, int &i, int &j)
{
    for (const food& food_: foods)
    {
        if (food_.x==i && food_.y==j) return true;
    }
    return false;
}

int main() {
    srand(time(NULL));

    const int width = 20;
    const int height = 10;

    static int size=0;

    vector<segment> snake;
    vector<food> foods;

    snake.push_back({width/2, height/2});
    snake.push_back({width/2-1, height/2});
    snake.push_back({width/2-2, height/2});

    bool this_snake=false;
 
    bool gameover = false;

    int count = 0;

    clock_t start_time = clock();
    
    while (!gameover)
    {
        if ((clock() - start_time) / CLOCKS_PER_SEC >= 2.5 && count<5) 
        {
            food cord_food = generateFood(foods, snake, width, height);
            foods.push_back(cord_food);
            count++;
            start_time = clock();
        }

        clearScreen();

        for (int j = 0; j<height; ++j)
        {
            for (int i=0; i<width; ++i)
            {
                for (int z=0; z<snake.size(); z++)
                {
                    if (snake[z].x==i && snake[z].y==j)
                    {
                        if (z==0) cout<<'@';
                        else cout<<'o';

                        this_snake=true;
                        break;
                    }
                    else this_snake=false;
                }
                
                if (!this_snake)
                {
                    if ( j==0 || j==(height-1) || i==0 || i==(width-1)) cout<<'#';
                    else if (isFoodAt(foods, i, j)) cout<<'*';
                    else cout<<' ';
                }
            }
            cout<<endl;
        }
        cout << "Position: (" << snake[0].x << ", " << snake[0].y << ")\n";
        cout << "Size: " << size<< endl;

        if (_kbhit())
        {
            char key = tolower(_getch());

            if (key=='w') 
            {
                // 1. Вычисляем новую позицию головы
                int newHeadX = snake[0].x;
                int newHeadY = snake[0].y - 1;  // для 'w'
                
                // 2. Проверяем столкновение с телом
                bool collision = false;
                for (int i = 1; i < snake.size(); i++) {  // начинаем с 1 (пропускаем голову)
                    if (snake[i].x == newHeadX && snake[i].y == newHeadY) {
                        collision = true;
                        break;  // нашли столкновение, дальше не проверяем
                    }    
                }
                
                // 3. Если столкновения нет — двигаем
                if (!collision && snake[0].y>1) {
                    // для поедания
                    segment tempTail= snake.back();
                    
                    for (int i = snake.size()-1; i>0; i--)
                    {
                        snake[i].x = snake[i-1].x;
                        snake[i].y = snake[i-1].y;
                    }
                    
                    snake[0].y--;
                    eating(foods, tempTail, snake, size, count);
                }
                else if (newHeadY!=snake[1].y) gameover=true;
            }

            if (key=='s') 
            {
                int newHeadX = snake[0].x;
                int newHeadY = snake[0].y + 1; 
                
                bool collision = false;
                for (int i = 1; i < snake.size(); i++) {  
                    if (snake[i].x == newHeadX && snake[i].y == newHeadY) {
                        collision = true;
                        break;  
                    }
                }

                if (!collision && snake[0].y<height-2) {

                    segment tempTail= snake.back();

                    for (int i = snake.size()-1; i>0; i--)
                    {
                        snake[i].x = snake[i-1].x;
                        snake[i].y = snake[i-1].y;
                    }

                    snake[0].y++;

                    eating(foods, tempTail, snake, size, count);
                }
                else if (newHeadY!=snake[1].y) gameover=true;
            }

            if (key=='a') 
            {
                int newHeadX = snake[0].x - 1;
                int newHeadY = snake[0].y; 
                
                bool collision = false;
                for (int i = 1; i < snake.size(); i++) {  
                    if (snake[i].x == newHeadX && snake[i].y == newHeadY) {
                        collision = true;
                        break;  
                    }
                }

                if (!collision && snake[0].x>1) {

                    segment tempTail= snake.back();

                    for (int i = snake.size()-1; i>0; i--)
                    {
                        snake[i].x = snake[i-1].x;
                        snake[i].y = snake[i-1].y;
                    }

                    snake[0].x--;

                    eating(foods, tempTail, snake, size, count);
                }
                else if (newHeadX!=snake[1].x) gameover=true;
            }

            if (key=='d') 
            {
                int newHeadX = snake[0].x + 1;
                int newHeadY = snake[0].y; 
                
                bool collision = false;
                for (int i = 1; i < snake.size(); i++) {  
                    if (snake[i].x == newHeadX && snake[i].y == newHeadY) {
                        collision = true;
                        break;  
                    }
                }

                if (!collision && snake[0].x<width-2) {

                    segment tempTail= snake.back();

                    for (int i = snake.size()-1; i>0; i--)
                    {
                        snake[i].x = snake[i-1].x;
                        snake[i].y = snake[i-1].y;
                    }

                    snake[0].x++;

                    eating(foods, tempTail, snake, size, count);
                }
                else if (newHeadX!=snake[1].x) gameover=true;
            }

            if (key=='q') gameover=true; //выход из игры
        }

        Sleep(100);
    }

    cout<<"gameover"<<endl;
    return 0;
}
