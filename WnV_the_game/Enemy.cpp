/*#include "Enemy.h"
#include <random>
#include <ctime>
#include "Entity.h"


using namespace std;

Enemy::Enemy(char tile, int attack, int defense, int health, int pot, int type) 
{

	_tile = tile;
	_attack = attack;
	_defense = defense;
	_health = health;
	_pot = pot;
	_type = type;

}
void Enemy::setPosition(int x, int y) { 
	_x = x;
	_y = y;
}

void Enemy::setHP(int h) {

	_health = h;
}

void Enemy::setStats() {

	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> atckRoll(1, 3);
	uniform_int_distribution<int> defRoll(1, 2);
	uniform_int_distribution<int> potRoll(0, 2);

	int atck = atckRoll(randomEngine);
	_attack = atck;
	int def = defRoll(randomEngine);
	_defense = def;
	int pot = potRoll(randomEngine);
	_pot = pot;



}
void Enemy::getPosition(int& x, int& y) {
	x = _x;
	y = _y;
}


void Enemy::getStats(int& a, int& d, int& h,int& p, int& type) {
	a = _attack;
	d = _defense;
	h = _health;
	p = _pot;
	type = _type;

}


char Enemy::getMove() {
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveRoll(0, 9);

	int randomMove = moveRoll(randomEngine);
	switch (randomMove) {
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	case 4:
		return 'q';
	case 5:
		return 'e';
	case 6:
		return 'z';
	case 7:
		return 'c';
	default:
		return '.';

	}
}
*/