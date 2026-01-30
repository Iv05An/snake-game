#include "../include/Game.h"

Game::Game(int width_, int height_): width(width_), height(height_)
{
    currentState = MAIN_MENU;
    size = 3;
    this_snake=false;
    gameover = false;
    count = 0;
}

int Game::gameLoop(gameState &currentState)
{
    srand(time(NULL));
    constexpr int GAME_SPEED_MS = 400;
    constexpr double FOOD_GENERATION_INTERVAL = 2.5;

    clock_t start_time = clock();
    
    while (!gameover)
    {
        SnakeBody = Snake.getBody();

        if ((clock() - start_time) / CLOCKS_PER_SEC >= FOOD_GENERATION_INTERVAL && count<5) 
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
        Sleep(GAME_SPEED_MS);

    }

    currentState = GAMEOVER;
    return Snake.getBody().size();
}

void Game::Run()
{
    // currentState = MAIN_MENU;
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
            clearScreen();
            string playerName;
            cout << "\nEnter your name: ";
            cin >> playerName;
            Record newRec(playerName, size);
            newRec.write_record();
            break;
        }
            
        case GAMEOVER:
            currentState=MAIN_MENU;
            showGAMEOVER();
            
            break;
        case RECORDS:
        {
            showRecords();
            
            currentState=MAIN_MENU;
            break;
        }
            
        default:
            break;
        }
    }
}
