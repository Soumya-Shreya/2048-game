#include "game.h"
#include <cstring>
#include <time.h>
#include <random>
#include <iostream>

using namespace std;

//The cnstructor fills 2 or 4 at any two random positions on the board and 0 elsewhere
//This also assigns maxformed value of 2 or 4 accordingly
game::game() {
    memset(board,0,4*4*sizeof(int));

    srand((unsigned)time(0));

    //The number generated is 2 90% of the time and 4 for the rest 10% cases
    int num = (double)rand()/(double)RAND_MAX;
    if(num<0.9) {
        num = 2;
    }
    else {
        num = 4;
    }

    int pos = rand()%16;    //choosing a position randomly out of 16 possible positions
    board[pos/4][pos%4] = num;
    maxformed = num;

    num = (double)rand()/(double)RAND_MAX;
    if(num<0.9) {
        num = 2;
    }
    else {
        num = 4;
    }

    int pos2 = rand()%16;   //If the randomly generated number was already filled, we need to generate a new position
    while(pos2==pos) {
        pos2 = rand()%16;
    }

    board[pos2/4][pos2%4] = num;
    maxformed = max(maxformed,num);
}


//Prints the gameboard on console
void game::display() {
    for(int i = 0; i<4; i++) {
        cout<<" ____";
    }
    cout<<endl;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            cout<<"|";
            if(board[i][j]) {
                printf("%4d",board[i][j]);
            }
            else {
                cout<<"    ";
            }
        }
        cout<<"|\n";
        for(int i = 0; i<4; i++) {
            cout<<" ____";
        }
        cout<<endl;

    }
}

//return 0 for playing state, 1 for winning state and 2 for loosing state
int game::lose()
{
    //Checks the maximum number formed so far to determine winning condition
    if(maxformed==2048) {
        return 1;
    }

    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<4; j++)
        {
            if(board[i][j]==0)      //If there is an empty cell on the board, it is a playing state
            {
                return 0;
            }

            //If two consecutive cells have equal values, it is a playing state
            if(j+1<4) {
                if(board[i][j+1]==board[i][j]) {
                    return 0;
                }
            }
            if(i+1<4) {
                if(board[i+1][j]==board[i][j]) {
                    return 0;
                }
            }
        }
    }

    //Loosing state
    return 2;
}

void game::moveleft() {
    bool change = false;    //stores if a change in the state of board happened after this move

    for(int i = 0; i<4; i++) {

        //stores true if the cell can not be merged with the next occupied cell. (Next takes its meaning relative to the move)
        //This happens if the value in next occupied cell was formed due to merging in the current move
        bool flag = false;
        for(int j = 1; j<4; j++) {
            if(!board[i][j]) {
                continue;
            }

            //Move towards left while you reach the end of board or an occupied cell
            int k = j-1;
            while(k>=0 && board[i][k]==0) {
                k--;
            }

            //If u reach end of board, simply shift that cell at the end of board
            if(k==-1) {
                board[i][0] = board[i][j];
                board[i][j] = 0;
                change = true;
                flag = false;
                continue;
            }

            //If it is not possible to merge either due to flag value or due to unequal values in the two cells
            //just shift the cell at the location right of the occupied cell found
            if(flag || board[i][k]!=board[i][j]) {
                board[i][k+1] = board[i][j];
                flag = false;

                //If the shifting actually happens
                if(k+1!=j) {
                    board[i][j] = 0;
                    change = true;
                }
            }

            //Merging needs to be done, since a bigger number is produced, maxformed needs to be updated as well
            else {
                board[i][k] += board[i][j];

                //Since the value of this cell was generated in this merging,
                //this cell is not available for merging to subsequent cells for the current merging
                flag = true;
                board[i][j] = 0;
                change = true;
                maxformed = max(maxformed,board[i][k]);
            }
        }
    }

    //If the state of board changed due to this move, introduce a new random cell in the game board
    //Else the move was useless, and nothing happens
    if(change) {
        int num = (double)rand()/(double)RAND_MAX;
        if(num<0.9) {
            num = 2;
        }
        else {
            num = 4;
        }

        int pos = rand()%16;
        while(board[pos/4][pos%4]) {
            pos = rand()%16;
        }
        board[pos/4][pos%4] = num;
    }
}

void game::moveright() {
    bool change = false;    //stores if a change in the state of board happened after this move
    for(int i = 0; i<4; i++) {

        //stores true if the cell can not be merged with the next occupied cell. (Next takes its meaning relative to the move)
        //This happens if the value in next occupied cell was formed due to merging in the current move
        bool flag = false;
        for(int j = 2; j>=0; j--) {
            if(!board[i][j]) {
                continue;
            }

            //Move towards right while you reach the end of board or an occupied cell
            int k = j+1;
            while(k<4 && board[i][k]==0) {
                k++;
            }

            //If u reach end of board, simply shift that cell at the end of board
            if(k==4) {
                board[i][3] = board[i][j];
                change = true;
                board[i][j] = 0;
                flag = false;
                continue;
            }

            //If it is not possible to merge either due to flag value or due to unequal values in the two cells
            //just shift the cell at the location right of the occupied cell found
            if(flag || board[i][k]!=board[i][j]) {
                board[i][k-1] = board[i][j];
                flag = false;

                //If the shifting actually happens
                if(k-1!=j) {
                    board[i][j] = 0;
                    change = true;
                }
            }

            //Merging needs to be done, since a bigger number is produced, maxformed needs to be updated as well
            else {
                board[i][k] += board[i][j];

                //Since the value of this cell was generated in this merging,
                //this cell is not available for merging to subsequent cells for the current merging
                flag = true;
                board[i][j] = 0;
                change = true;
                maxformed = max(maxformed,board[i][k]);
            }
        }
    }

    //If the state of board changed due to this move, introduce a new random cell in the game board
    //Else the move was useless, and nothing happens
    if(change) {
        int num = (double)rand()/(double)RAND_MAX;
        if(num<0.9) {
            num = 2;
        }
        else {
            num = 4;
        }

        int pos = rand()%16;
        while(board[pos/4][pos%4]) {
            pos = rand()%16;
        }
        board[pos/4][pos%4] = num;
    }
}

void game::moveup() {
    bool change = false;    //stores if a change in the state of board happened after this move
    for(int j = 0; j<4; j++) {

        //stores true if the cell can not be merged with the next occupied cell. (Next takes its meaning relative to the move)
        //This happens if the value in next occupied cell was formed due to merging in the current move
        bool flag = false;
        for(int i = 1; i<4; i++) {
            if(!board[i][j]) {
                continue;
            }

            //Move up while you reach the end of board or an occupied cell
            int k = i-1;
            while(k>=0 && board[k][j]==0) {
                k--;
            }

            //Move up while you reach the end of board or an occupied cell
            if(k==-1) {
                board[0][j] = board[i][j];
                board[i][j] = 0;
                change = true;
                flag = false;
                continue;
            }

            //If it is not possible to merge either due to flag value or due to unequal values in the two cells
            //just shift the cell at the location right of the occupied cell found
            if(flag || board[k][j]!=board[i][j]) {
                board[k+1][j] = board[i][j];
                flag = false;

                //If the shifting actually happens
                if(k+1!=i) {
                    board[i][j] = 0;
                    change = true;
                }
            }

            //Merging needs to be done, since a bigger number is produced, maxformed needs to be updated as well
            else {
                board[k][j] += board[i][j];

                //Since the value of this cell was generated in this merging,
                //this cell is not available for merging to subsequent cells for the current merging
                flag = true;
                board[i][j] = 0;
                change = true;
                maxformed = max(maxformed,board[k][j]);
            }
        }
    }

    //If the state of board changed due to this move, introduce a new random cell in the game board
    //Else the move was useless, and nothing happens
    if(change) {
        int num = (double)rand()/(double)RAND_MAX;
        if(num<0.9) {
            num = 2;
        }
        else {
            num = 4;
        }

        int pos = rand()%16;
        while(board[pos/4][pos%4]) {
            pos = rand()%16;
        }
        board[pos/4][pos%4] = num;
    }
}

void game::movedown() {
    bool change = false;    //stores if a change in the state of board happened after this move
    for(int j = 0; j<4; j++) {

        //stores true if the cell can not be merged with the next occupied cell. (Next takes its meaning relative to the move)
        //This happens if the value in next occupied cell was formed due to merging in the current move
        bool flag = false;
        for(int i = 2; i>=0; i--) {
            if(!board[i][j]) {
                continue;
            }

            //Move down while you reach the end of board or an occupied cell
            int k = i+1;
            while(k>=0 && board[k][j]==0) {
                k++;
            }

            //Move up while you reach the end of board or an occupied cell
            if(k==-1) {
                board[0][j] = board[i][j];
                board[i][j] = 0;
                change = true;
                flag = false;
                continue;
            }

            //If it is not possible to merge either due to flag value or due to unequal values in the two cells
            //just shift the cell at the location right of the occupied cell found
            if(flag || board[k][j]!=board[i][j]) {
                board[k-1][j] = board[i][j];
                flag = false;

                //If the shifting actually happens
                if(k-1!=i) {
                    board[i][j] = 0;
                    change = true;
                }
            }

            //Merging needs to be done, since a bigger number is produced, maxformed needs to be updated as well
            else {
                board[k][j] += board[i][j];

                //Since the value of this cell was generated in this merging,
                //this cell is not available for merging to subsequent cells for the current merging
                flag = true;
                board[i][j] = 0;
                change = true;
                maxformed = max(maxformed,board[k][j]);
            }
        }
    }

    //If the state of board changed due to this move, introduce a new random cell in the game board
    //Else the move was useless, and nothing happens
    if(change) {
        int num = (double)rand()/(double)RAND_MAX;
        if(num<0.9) {
            num = 2;
        }
        else {
            num = 4;
        }

        int pos = rand()%16;
        while(board[pos/4][pos%4]) {
            pos = rand()%16;
        }
        board[pos/4][pos%4] = num;
    }
}
