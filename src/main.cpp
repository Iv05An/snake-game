#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

void clearScreen()
{
    system("clear");
}

void cord(int& foodX, int& foodY, const int& width, const int& height, int& playerX, int& playerY)
{
    bool valid = false;
    while (!valid)
    {
        foodX = 1 + rand() % (width - 2);   // от 1 до width-2
        foodY = 1 + rand() % (height - 2);  // от 1 до height-2
      
        if (foodX != playerX || foodY != playerY) 
        {
            valid = true;
        }
    }
}

int main() {
    srand(time(NULL));

    const int width = 20;
    const int height = 10;

    int playerX = width/2;
    int playerY = height/2;

    int foodX;
    int foodY;

    bool gameover = false;

    int size=0;
    cord(foodX, foodY, width, height, playerX, playerY); 

    while (!gameover)
    {
        clearScreen();

        if (playerX==foodX && playerY==foodY)
        {
            size++;
            cord(foodX, foodY, width, height, playerX, playerY);
        }
        for (int j = 0; j<height; ++j)
        {
            for (int i=0; i<width; ++i)
            {
                if ( ( playerX)==i && (playerY)==j) cout<<'@';
                else if ( j==0 || j==(height-1) || i==0 || i==(width-1)) cout<<'#';
                else if (foodX==i && foodY==j) cout<<'*';
                else cout<<' ';
                
                                         
            }
            cout<<endl;
        }
        cout << "Position: (" << playerX << ", " << playerY << ")\n";
        cout << "Size: " << size<< endl;
        if (_kbhit())
        {
            char key = tolower(_getch());
            if (key=='w') playerY--;
            if (key=='s') playerY++;
            if (key=='d') playerX++;
            if (key=='a') playerX--;
            if (key=='q') gameover=true; //выход из игры
        }


        if (playerX>=width-1) playerX=width-2;
        if (playerX<=1) playerX=1;
        if (playerY<=1) playerY=1;
        if (playerY>=height-1) playerY=height-2;

        Sleep(100);
    }

    return 0;
}
