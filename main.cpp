/*
2048 game
Use 2,4,6,8, to go down, left, right, up respectively.

Created by Soumya Shreya
*/

#include "game.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main()
{
    game g;
    g.display();
    int status = g.lose();      //status is 0 when u need to continue the game, 1 if you won and 2 if you lose
    while(!status)
    {
        char n = getch();
        system("cls");
        switch(n)
        {
        case '8':
            g.moveup();
            break;
        case '4':
            g.moveleft();
            break;
        case '6':
            g.moveright();
            break;
        case '2':
            g.movedown();
            break;
        }
        g.display();
        status = g.lose();
    }

    if(status==1) {
        cout<<"You Won!!!!";
    }
    else {
        cout<<"You Lost:(";
    }

    return 0;
}
