#include "../include/Menu.h"


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

void showGAMEOVER ()
{
    clearScreen();
    cout<<"GAMEOVER===GAMEOVER===GAMEOVER";
    Sleep(1000);
}

void showRecords()
{
    vector<Record>records_vec = Record::records_vector();
    Record::print_records(records_vec);
    cout<<"Enter q for exit: ";
    char ch;
    while(!((cin>>ch)&&ch=='q'))
    {}
}