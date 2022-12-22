#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <string>

using namespace std;

class Level
{
public:
	Level();

	void build(int x,int y); //random initializer that saves generated map on file

	void load(string fileName,Player &player); //back from generated file to vector to manage "graphics"
	void print();                          //graphic printer onto terminal screen

	void usePot(Player& player);            //obj player function to heal chosen team

	void movePlayer(char input, Player &player);  //moving function based on input
	void updateEnemy();                            //random generated enemies moving algorithm
	char getTile(int x, int y);                   //char returning from "map" vector levelData
	void setTile(int x, int y, char tile);       //char setting in vector levelData
	void interact(int enemyIndex,int i);         //enemies combat/help interactions

	void enemyGrit();                          //enemies interaction loop
	 

private:
	void processPlayerMove(Player& player, int targetX, int targetY);  //used by movePlayer function to determine available movement and vector updating
	void processEnemyMove(int enemyIndex, int targetX, int targetY);   // used by updateEnemy function to determine available movement and vector updating


private:
	vector <Enemy> _enemies;  //vector to save Enemy objects
	vector <string> _levelData;  //vector to save every objects coordinates
	vector <unsigned char> _levelCreate; //vector used in generation of map


};

