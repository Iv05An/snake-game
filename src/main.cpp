#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>

using namespace std;

void clearScreen()
{
    system("clear");
}

struct segment
{
    int x, y;
};

void cord(int& foodX, int& foodY, const int& width, const int& height, const vector<segment> &snake)
{
    bool valid = false;
    while (!valid)
    {
        foodX = 1 + rand() % (width - 2);   // от 1 до width-2
        foodY = 1 + rand() % (height - 2);  // от 1 до height-2
      
        for (int i=0; i<snake.size(); i++)
        {
            if (foodX == snake[i].x && foodY == snake[i].y) 
            {
                valid = false;
                continue;
            }
            valid = true;
        }
    }
}

void eating(int& foodX, int& foodY, const int& width, const int& height, segment &tail, vector<segment> &snake, int &size)
{
    if (snake[0].x==foodX && snake[0].y==foodY)
    {
        snake.push_back({tail.x, tail.y});
        size++;
        cord(foodX, foodY, width, height, snake);
    }
}

int main() {
    srand(time(NULL));

    const int width = 20;
    const int height = 10;

    static int size=0;

    vector<segment> snake;

    snake.push_back({width/2, height/2});
    snake.push_back({width/2-1, height/2});
    snake.push_back({width/2-2, height/2});

    bool this_snake=false;
    int foodX;
    int foodY;

    bool gameover = false;

    cord(foodX, foodY, width, height, snake); 

    while (!gameover)
    {
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
                    else if (foodX==i && foodY==j) cout<<'*';
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
                    eating(foodX, foodY, width, height, tempTail, snake, size);
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
                    eating(foodX, foodY, width, height, tempTail, snake, size);
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
                    eating(foodX, foodY, width, height, tempTail, snake, size);
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
                    eating(foodX, foodY, width, height, tempTail, snake, size);
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
