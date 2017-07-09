class game {
    int board[4][4];    //actual 4*4 board where u play
    int maxformed;      //stores the maximum number formed so far on the game board

public:
    game();

    // prints the board on the console
    void display();

    //return 0 to indicate running game, 1 to indicate winning state and 2 to indicate losing state
    int lose();

    //called on pressing up button i.e., 8
    void moveup();

    //called on pressing down button i.e., 2
    void movedown();

    //called on pressing left button i.e., 4
    void moveleft();

    //called on pressing right button i.e., 6
    void moveright();
};
