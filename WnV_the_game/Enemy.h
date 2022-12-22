#pragma once
#include <string>
#include <random>
#include <ctime>

class Enemy
{
public:
	Enemy(char tile, int attack, int defense, int health, int pot,int type);  //constructor

	void setPosition(int x, int y); //position update in vector levelData

	void setStats(); //random initializer for enemy attack,defence and available potions

	void setHP(int h);  //access to HP private variable


	int getHP() {return _health; } //current enemy health reamaining

	void getPosition(int &x, int &y); //current enemy position information

	bool getType(){ return _type; } //enemy type (Warewolve or Vampire)
	char getTile() { return _tile; } //current enemy graphic information 
	char getMove();                  //enemy's random move generator
	void getStats(int& a, int& d, int& h, int& p, int& type); //access to enemy's private variables

private:

	char _tile;

	int _type;
	int _defense;
	int _attack;
	int _health;
	int _pot;

	int _x;
	int _y;
	
};

