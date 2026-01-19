#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

void clearScreen()
{
    system("clear");
}

int main() {
    const int width = 20;
    const int height = 10;

    int playerX = width/2;
    int playerY = height/2;

    bool gameover = false;

    while (!gameover)
    {
        clearScreen();

        for (int j = 0; j<height; ++j)
        {
            for (int i=0; i<width; ++i)
            {
                if ( ( playerX-1)==i && (playerY-1)==j) cout<<'@';
                else if ( j==0 || j==(height-1) || i==0 || i==(width-1)) cout<<'#';
                else cout<<' ';
            }
            cout<<endl;
        }
        cout << "Position: (" << playerX << ", " << playerY << ")\n";
        if (_kbhit())
        {
            char key = tolower(_getch());
            if (key=='w') playerY--;
            if (key=='s') playerY++;
            if (key=='d') playerX++;
            if (key=='a') playerX--;
            if (key=='q') gameover=true; //выход из игры
        }


        if (playerX>=width-1) playerX=width-1;
        if (playerX<=1) playerX=2;
        if (playerY<=1) playerY=2;
        if (playerY>=height-1) playerY=height-1;

        Sleep(100);
    }

    return 0;
}
