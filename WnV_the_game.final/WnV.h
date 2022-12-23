#pragma once
#include <string>
#include "conio.h"
#include "Level.h"

using namespace std;



class WnV  // class that is calling main functions and manages input and output
{

public:
    WnV(string levelFileName);

    void playGame();
    void playerMove();
    int turnCount(int& _i, bool& _turn);


private:

        Level _level;   //obj Level construction
        Player _player; //obj Player construction
};