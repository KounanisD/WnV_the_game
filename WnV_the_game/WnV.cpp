#include "WnV.h"
#include "Player.h"
#include <iostream>
#include <conio.h>
#include "Enemy.h"



bool turn = true; 
int _tpt;

WnV::WnV(string levelFileName) {  //constructor/initializer function to get team and map size and call level builder
	char team;
	int sizex;
	int sizey;

	cout << "Welcome to WnV....\n";
	system("PAUSE");
	system("cls");
	cout << "To move around the map press w,a,s,d, accordingly...\n";
	system("PAUSE");
	system("cls");
	cout << "To pause the game and get informations about the game press q...\n";
	system("PAUSE");
	system("cls");
	cout << "If at any time you wish to leave press esc...\n";
	system("PAUSE");
	system("cls");
	cout << "Let's the fun begin...\n";
	system("PAUSE");
	system("cls");
	cout << "Press W or V to choose side...\n";

error:
	cin >> team;

	switch (team) {
	    case 'W':
		case 'w':
			_tpt = 1;
			_player.init(1,1);
			break;
		case 'V':
		case 'v':
			_tpt = 0;
			_player.init(1, 0);
			break;
		default:
			cout << "Invalid input, try again(W or V)\n";
			goto error;
	}
	cout << "Now enter the height of the map, 6 up to 100\n";

	errorx:
	cin >> sizex;

		if ((sizex < 6) || (sizex > 100)) {

		cout << "Invalid input, try again(6 between 100)\n";

		cin.clear();

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cin >> sizex;

		goto errorx;
	}

	cout << "And again for the width,6 up to 100\n";

errory:

	cin >> sizey;

	if ((sizey < 6) || (sizey > 100)) {

		cout << "Invalid input, try again(6 between 100)\n";

		cin.clear();

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cin >> sizey;

		goto errory;
	}

	_level.build(sizex,sizey);

	_level.load(levelFileName, _player);
	

	system("PAUSE");
}

void WnV::playGame() { //game loop, exits at end of game or after player choice.Calls main functions

	bool isDone = false;
	int i=0;

	while (isDone != true) {
		system("cls");
		_level.print();
		_level.enemyGrit();
		turnCount(i, turn);
		playerMove();
		_level.updateEnemy();
	}


}
void WnV::playerMove() { //player input manager,calling main moving function and handling some exceptions

	char input;
	extern int Wcount;
	extern int Vcount;

	cout << "enter a move\n";

	input = _getch();

	if (input == 27) {
		exit(1);
	}

	if ((input == 'q') || (input == 'Q')) {
		cout << "Remaning Pots: " << _player.getPot() << '\n';
		cout << "Remaning Werewolves:" << Wcount << ("\n");
		cout << "Remaning Vampires:" << Vcount << ("\n");
		system("PAUSE");
		input = _getch();
	}
	_level.movePlayer(input, _player);
}
int  WnV::turnCount(int& _i,bool& _turn) {  //day/night counter,day/night cycle is 15 steps
	if (_i == 15) {
		_turn = !_turn;
		_i = 0;
	}
	_i++;

	if (turn == 0) {
		cout << "The sun is bright for " << _i << "/15 turns \n";
	}
	else{
		
		cout << "The night is dark for " << _i << "/15 turns \n";
		}

	return _i;
	return _turn;
}