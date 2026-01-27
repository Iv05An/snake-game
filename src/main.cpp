#include <iostream>
#include "Food.h"
#include "Snake.h"
#include "segment.h"

#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <array>
#include <ctime>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <algorithm>
#define N 5
#define limit 10

using namespace std;

struct record_n
{
    string name;
    int size;
    time_t timestamp;
};

enum gameState
{
    MAIN_MENU,
    PLAYING,
    GAMEOVER,
    RECORDS
};

void clearScreen()
{
    system("clear");
}

int gameLoop(gameState &currentState)
{
    srand(time(NULL));

    const int width = 20;
    const int height = 10;

    int size=3;

    Snake Snake(width/2, height/2, size);
    vector<segment> SnakeBody;
    vector<Food> foods;

    bool this_snake=false;
 
    bool gameover = false;

    int count = 0;

    clock_t start_time = clock();
    
    while (!gameover)
    {
        SnakeBody = Snake.getBody();

        if ((clock() - start_time) / CLOCKS_PER_SEC >= 2.5 && count<5) 
        {
            Food cord_food = Food::generateFood(SnakeBody, foods, width, height);
            foods.push_back(cord_food);
            count++;
            start_time = clock();
        }

        clearScreen();

        for (int j = 0; j<height; ++j)
        {
            for (int i=0; i<width; ++i)
            {
                for (int z=0; z<SnakeBody.size(); z++)
                {
                    if (SnakeBody[z].x==i && SnakeBody[z].y==j)
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
                    else if (Food::isFoodAt(foods, i, j)) cout<<'*';
                    else cout<<' ';
                }
            }
            cout<<endl;
        }
        cout << "Position: (" << SnakeBody[0].x << ", " << SnakeBody[0].y << ")\n";
        cout << "Size: " << size<< endl;

        if (_kbhit())
        {
            char key = tolower(_getch());

            if (key=='w') 
            {
                Snake.setDirection(UP);
            }

            if (key=='s') 
            {
                Snake.setDirection(DOWN);
            }

            if (key=='a') 
            {
                Snake.setDirection(LEFT);
            }

            if (key=='d') 
            {
                Snake.setDirection(RIGHT);
            }

        }

        if (!Snake.valide_collisionWithWall(width, height)||Snake.truthCollision())
        {
            gameover = true;
            break; // Выходим из цикла сразу
        }

        Snake.move();

        Snake.eating(foods, count);
        Sleep(400);

    }

    currentState = GAMEOVER;
    return Snake.getBody().size();
}

void showMainMenu(gameState &currentState)
{
    int input;
    clearScreen();

    cout<<"========SNAKE========"<<endl;
    cout<<"FOR START GAME ENTER:"<<endl;
    cout<<"-1 START"<<endl;
    cout<<"-2 table of records"<<endl;
    cout<<"-3 exit"<<endl;

    while (!(cin>>input)||input<1||input>3)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        clearScreen();
        cout<<"Enter an integer value of 1, 2, or 3"<<endl;
        Sleep(1000);
        clearScreen();
        
        cout<<"========SNAKE========"<<endl;
        cout<<"FOR START GAME ENTER:"<<endl;
        cout<<"-1 START"<<endl;
        cout<<"-2 table of records"<<endl;
        cout<<"-3 exit"<<endl;

    }

    switch (input)
    {
    case 1 :
        currentState=PLAYING;
        break;
    case 2 :
        currentState=RECORDS;
        break;
    case 3 :
        exit(0);
        break;   
    default:
        break;
    }
}

void write_record(int &size)
{
    clearScreen;
    string name;
    cout<<"enter name: ";
    cin>>name;

    time_t timestamp  = time(nullptr);

    ofstream file("records.txt", ios::app);
    file<<name<<" "<<size<<" "<<timestamp<<endl;

    file.close();
}

vector<record_n> records_vector()
{
    vector<record_n> records;
    record_n record;
    ifstream file("records.txt");
    if (!file) {
        cout << "Файл рекордов не найден, создаём новый" << endl;
        return records;
    }
    
    while(file>>record.name>>record.size>>record.timestamp)
    {
        records.push_back(record);
    }
    file.close();
    return records;
}

void print_records(vector<record_n> &records_vector)
{
    sort(records_vector.begin(), records_vector.end(), [](const record_n &a, const record_n &b) {
        if (a.size!=b.size) return a.size>b.size;
        return a.timestamp>b.timestamp;
    });

    int top_count=min(10, (int)records_vector.size());
    tm *local_time;
    char buffer[80];
    cout<<"=======RECORDS======="<<endl;
    cout<<"name    count    date"<<endl;
    for (int i =0; i<top_count; ++i)
    {
        local_time = localtime(&records_vector[i].timestamp);
        strftime(buffer, 80, "%d.%m.%Y %H:%M", local_time);
        cout<<records_vector[i].name<<'\t'<<records_vector[i].size<<'\t'<<buffer<<endl;
    }
}

int main() {
    gameState currentState = MAIN_MENU;
    while (true)
    {
        switch (currentState)
        {
        case MAIN_MENU:
            showMainMenu(currentState);
            break;
        case PLAYING:
        {
            int size = gameLoop(currentState);
            write_record(size);
            break;
        }
            
        case GAMEOVER:
            currentState=MAIN_MENU;
            clearScreen();
            cout<<"GAMEOVER===GAMEOVER===GAMEOVER";
            Sleep(1000);
            break;
        case RECORDS:
        {
            vector<record_n>records_vec = records_vector();
            print_records(records_vec);
            cout<<"Enter q for exit: ";
            char ch;
            while(!((cin>>ch)&&ch=='q'))
            {}
            currentState=MAIN_MENU;
            break;
        }
            
        default:
            break;
        }
    }
    
    
    return 0;
}
