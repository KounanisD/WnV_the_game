#pragma once
#include <string>
#include <random>
#include <ctime>
#include<iostream>
#include <cstdlib>
#include <vector>


class Entity
{

public:
	Entity();  //constructor

		void setPosition(int x, int y); //position update in vector levelData

        void getPosition(int& x, int& y); //current enemy position information

		//bool getType() { return _type; } //enemy type (Warewolve or Vampire)

		//void getStats(int& a, int& d, int& h, int& p, int& type); //access to enemy's private variables



private:

	int _x;
	int _y;
};


class Enemy: public Entity
{
public:
	Enemy(char tile, int attack, int defense, int health, int pot, int type) ;  //constructor

	Enemy() {}

	void setStats(); //random initializer for enemy attack,defence and available potions

	void setHP(int h);  //access to HP private variable

	int getHP() { return _health; } //current enemy health reamaining

	bool getType() { return _type; } //enemy type (Warewolve or Vampire)
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

class Player : public Entity  //active players class(program user avatar)
{

public:

	Player(int pot, int pt) : _pot(0), _pt(0) {};

	Player() {};

	void init(int pot,int pt);  //team choise getting func

	void setPot();  //potion add function in case the current tile is potion tile

	int getTeam() { return _pt; }   // current player team choice

	int  getPot() { return _pot; }  // number of available pots

	int checkPot(int& pot, bool turn, int pt);  //function that determines if use of player potion is currently available

private:

	int _pot; //available potions counter
	int _pt;  //team choice variable pt=player team
	int _x;
	int _y;
};
