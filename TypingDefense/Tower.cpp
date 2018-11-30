#include "Tower.h"

double Tower::jarak(Monster * monsterNear)
{
	double res = sqrt(pow(x - monsterNear->getX(),2) + pow(y - monsterNear->getY(),2));
	return res;
}

Tower::Tower(int x, int y, vector<Monster*> *allMonster)
{
	this->attackPoint = 10;
	this->x = x;
	this->y = y;
	this->radius = 140;
	this->s = 30;
	level = 1;
	this->allMonster = allMonster;
}


Tower::~Tower()
{
}
