#include "Player.h"





Player::Player() {

	_pot = 0;  
	_x = 0;
	_y = 0;
	_pt = 0;   
}

void Player::init(int pot, int pt) {

	_pot = pot;
	_pt = pt;

}
void Player::setPosition(int x, int y) { 
	_x = x;
	_y = y;
}
void Player::setPot() {       

	_pot++;
}


void Player::getPosition(int &x, int &y) { 
	x = _x;
	y = _y;
}


int Player::checkPot(int& pot, bool turn, int pt) { 
	pot = _pot;
	_pt = pt;
	if ((pot > 0) && (pt == turn)) {
		_pot--;
		return 1;
	}
	else return 0;
}