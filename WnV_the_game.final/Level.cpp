#include "Level.h"
#include "WnV.h"
#include "Entity.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>



int Wcount = 0; //global variables to use later for enemies count
int Vcount = 0; //global variables to use later for enemies count


Level::Level() {
}

void Level::build(int x, int y) {

	extern int _tpt;

	redo:
	int wcount = ((x * y) / 15);
	int vcount = ((x * y) / 15);
	int potcount = 1;
	int avacount = 1;
	int treecount = ((x * y) / 15);
	int watercount = ((x * y) / 15);
	int tilecount = (((x * y) * 3) / 4);
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> tileRoll(0, 15);

	x += 2;
	y += 2;

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {

			if ((i == 0) || (i == (x - 1)) || (j == 0) || (j == (y - 1))) {
				_levelCreate.push_back('#');
			}
			else {
			done:
				int tileSet = tileRoll(randomEngine);

				switch (tileSet) {
				case 0:
					if (wcount > 0) {
						_levelCreate.push_back('W');
						--wcount;
						break;
					}
					else {
						goto done;
					}
				case 1:
					if (vcount > 0) {
						_levelCreate.push_back('V');
						--vcount;
						break;
					}
					else {
						goto done;
					}
				case 2:
					if (potcount > 0) {
						_levelCreate.push_back('P');
						--potcount;
						break;
					}
					else {
						goto done;
					}
				case 3:
					if (avacount > 0) {
						if (_tpt == 0) {
							_levelCreate.push_back('&');
							--avacount;
						}
						else {
							_levelCreate.push_back('@');
							--avacount;
						}
						break;
					}
					else {
						goto done;
					}
				case 4:
					if (treecount > 0) {
						_levelCreate.push_back('^');
						--treecount;
						break;
					}
					else {
						goto done;
					}
				case 5:
					if (watercount > 0) {
						_levelCreate.push_back('~');
						--watercount;
						break;
					}
					else {
						goto done;
					}
				default:
					if (tilecount > 0) {
						_levelCreate.push_back('.');
						--tilecount;
					}
					else {
						goto done;
					}
					break;
				}
			}
		}
		_levelCreate.push_back('\n');

		string pathname("output.bin");

		ofstream textout(pathname.c_str(), ios::out | ios::binary);

		textout.write((const char*)&_levelCreate[0], _levelCreate.size());
	}

	if ((wcount > 0) || (vcount > 0) || (potcount > 0) || (avacount > 0)) {
		_levelCreate.clear();
		remove("output.bin");
		x -= 2;
		y -= 2;
		system("cls");
		goto redo;
	}
	_levelCreate.clear();
}



void Level::load(string fileName,Player& player) {

	ifstream file;

	file.open(fileName);
	if (file.fail()) {
		perror(fileName.c_str());
		system("PAUSE");
		exit(1);

	}
	string line;

	while (getline(file, line)) {
		_levelData.push_back(line);
	}

	file.close();

	char tile;


	for (int i = 0; i < _levelData.size(); i++) {
		for (int j = 0; j < _levelData[i].size(); j++) {
			tile = _levelData[i][j];

			switch (tile) {
			case '&':
			case '@':
				player.setPosition(j, i);
				break;
			case 'W':
				_enemies.push_back(Enemy(tile,0,0,0,3,0));
				_enemies.back().setStats();
				_enemies.back().setPosition(j, i);
				++Wcount;
				break;
			case 'V':
				_enemies.push_back(Enemy(tile, 0, 0, 0, 3, 1));
				_enemies.back().setStats();
				_enemies.back().setPosition(j, i);
				++Vcount;
				break;

			}
		}
	}
}
		void Level::print() {


				for (int i = 0; i < _levelData.size(); i++) {
					printf("%s\n", _levelData[i].c_str());
				}
			printf("\n");
		}
		void Level::movePlayer(char input, Player &player) {

			int playerX;
			int playerY;
			player.getPosition(playerX, playerY);

			switch (input) {
			case 'w':
			case 'W':
				processPlayerMove(player, playerX, playerY - 1);
				break;
			case 's':
			case 'S':
				processPlayerMove(player, playerX, playerY + 1);
				break;
			case 'a':
			case 'A':
				processPlayerMove(player, playerX - 1, playerY);
				break;
			case 'd':
			case 'D':
				processPlayerMove(player, playerX + 1, playerY);
				break;
			case 'r':
			case 'R':
				usePot(player);
				break;
			default:
				cout << "bad boi\n";
				system("PAUSE");
				break;
			}
		}	
		void Level::updateEnemy() {

			char aiMove;
			int enemyX;
			int enemyY;
			for (int i = 0; i < _enemies.size(); i++) {
				aiMove = _enemies[i].getMove();
				_enemies[i].getPosition(enemyX, enemyY);
 
				switch (aiMove) {
				case 'w':
					processEnemyMove(i, enemyX, enemyY - 1);
					break;
				case 's':
					processEnemyMove(i, enemyX, enemyY + 1);
					break;
				case 'a':
					processEnemyMove(i, enemyX - 1, enemyY);
					break;
				case 'd':
					processEnemyMove(i, enemyX + 1, enemyY);
					break;
				case 'q':
					if (_enemies[i].getType()) {
						processEnemyMove(i, enemyX - 1, enemyY - 1);
						break;
					}
					else
					break;
				case 'e':
					if (_enemies[i].getType()) {
						processEnemyMove(i, enemyX + 1, enemyY - 1);
						break;
					}
					else
					break;
				case 'z':
					if (_enemies[i].getType()) {
					   processEnemyMove(i, enemyX - 1, enemyY + 1);
					   break;
				    }
					else
					break;
				case 'c':
					if (_enemies[i].getType()) {
					  processEnemyMove(i, enemyX + 1, enemyY + 1);
					  break;
			        }
					else
					break;
				}
			}
		}


		char Level::getTile(int x, int y) {
			return _levelData[y][x];
		}

		void Level::setTile(int x, int y, char tile) {
			_levelData[y][x] = tile;
		}

			void Level::processPlayerMove(Player &player, int targetX, int targetY) {

				extern int _tpt;

				int playerX;
				int playerY;
				player.getPosition(playerX, playerY);
				char moveTile = getTile(targetX, targetY);

				switch (moveTile) {
				case '#':
					break;
				case '.':
					if (_tpt == 0) {
						player.setPosition(targetX, targetY);
						setTile(playerX, playerY, '.');
						setTile(targetX, targetY, '&');
					}
					else {
						player.setPosition(targetX, targetY);
						setTile(playerX, playerY, '.');
						setTile(targetX, targetY, '@');

						}					
					break;
				case 'P':
					if (_tpt == 0) {
						player.setPosition(targetX, targetY);
						setTile(playerX, playerY, '.');
						setTile(targetX, targetY, '&');
					}
					else {
						player.setPosition(targetX, targetY);
						setTile(playerX, playerY, '.');
						setTile(targetX, targetY, '@');

					}
					player.setPot();
					break;
				}
			
			}

			void Level::processEnemyMove(int enemyIndex, int targetX, int targetY) {
				  
				int enemyX;
				int enemyY;

				_enemies[enemyIndex].getPosition(enemyX, enemyY);

				char moveTile = getTile(targetX, targetY);

				switch (moveTile) {
				case '#':
					break;
				case '.':
					_enemies[enemyIndex].setPosition(targetX, targetY);
					setTile(enemyX, enemyY, '.');
					setTile(targetX, targetY, _enemies[enemyIndex].getTile());
					break;
				}
		    }

		


			void Level::enemyGrit() {

			
				int enemyX, enemyY;
				int targetX, targetY;

				for (int i = 0; i < _enemies.size(); i++) {

					_enemies[i].getPosition(enemyX, enemyY);

					for (int j = 0; j < _enemies.size(); j++) {

						 _enemies[j].getPosition(targetX, targetY);

						if (((enemyX + 1) == targetX) && (targetY == enemyY)) {

							interact(i, j);

						}
						else if ((targetX == enemyX) && ((enemyY + 1) == targetY)) {

							interact(i, j);

						}
						else if ((targetX == enemyX) && ((enemyY - 1) == targetY)) {

							interact(i, j);

						}
						else if (((enemyX - 1) == targetX) && (targetY == enemyY)) {

							interact(i, j);

						}


					}
				}
			}
			void Level::interact(int enemyIndex, int targetIndex) {

				extern int _tpt;

				int X, enemyX;
				int Y, enemyY;
				int a, enemya;
				int d, enemyd;
				int h, enemyh;
				int p, enemyp;
				int type, enemytype;



				_enemies[enemyIndex].getPosition(enemyX, enemyY);
				_enemies[enemyIndex].getStats(enemya, enemyd, enemyh, enemyp, enemytype);
				_enemies[targetIndex].getPosition(X, Y);
				_enemies[targetIndex].getStats(a, d, h, p, type);

				static default_random_engine randomEngine(time(NULL));
				uniform_int_distribution<int> healRoll(0, 1);


					if ((enemytype == type) && healRoll(randomEngine)) {
						if ((enemyp > 0) && (h < 3)) {
							enemyp--;
							h++;
							_enemies[targetIndex].setHP(h);

						}
					}


					

					if (enemytype != type) {


						if ((enemya >= a) && ((enemya - d) > 0)) {

							h = (h - (enemya - d));

							_enemies[targetIndex].setHP(h);

							if (h <= 0) {

								setTile(X, Y, '.');

								_enemies[targetIndex] = _enemies.back();
								_enemies.pop_back();
								targetIndex--;
								enemyIndex--;
								switch (type) {
								case 0:
									Wcount--;
									if (Wcount == 0) {
										cout << "The Werewolves are dead ! \n";
										if ( _tpt == type) {
											cout << "YOU ARE A BIG LOOSER! \n";
											exit(0);
										}
										else {
											cout << "ARE YOU HAPPY NOW? \n";
											exit(1);
										}
									}
									break;
								case 1:
									Vcount--;
									if (Vcount == 0) {
										cout << "The Vampires are dead ! \n";
										if (_tpt == type) {
											cout << "YOU ARE A BIG LOOSER! \n";
											exit(0);
										}
										else {
											cout << "ARE YOU HAPPY NOW? \n";
											exit(1);
										}
									}
									break;
								}
							}
						}
					}
					}

			void Level::usePot(Player &player) {

				bool pt = player.getTeam();
				int pot = player.getPot();
				extern bool turn;

				switch (player.checkPot(pot,turn,pt)){
					case 0:

						cout << "You can't do that \n  Press Q to see if you have pots left\n";
						cout << "Remember you can heal W only during night and V during day\n";
						system("PAUSE");

						break;
					case 1:

						cout << "POTION USED!!!\n";
						system("PAUSE");
						for (int i = 0; i < _enemies.size(); i++) {
							if ((pt != _enemies[i].getType()) && (_enemies[i].getHP() < 3)) {
								_enemies[i].setHP(3);
							}

						}
						break;
			            } 
				
				return;
			}