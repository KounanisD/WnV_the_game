#pragma once
#include<iostream>
#include <string>
#include <cstdlib>
#include <vector>


class Player  //active players class(program user avatar)
{

public:

	Player();

	void init(int pot, int pt);  //team choise getting func

	void setPosition(int x, int y); //position update in vector levelData

	void setPot();  //potion add function in case the current tile is potion tile

	void getPosition(int& x, int& y); //current player position information
	
	int getTeam() { return _pt; }   // current player team choice

	int  getPot() { return _pot; }  // number of available pots

	int checkPot(int& pot, bool turn, int pt);  //function that determines if use of player potion is currently available

private:

	int _pot; //available potions counter
	int _pt;  //team choice variable pt=player team
	int _x;
	int _y;
};
