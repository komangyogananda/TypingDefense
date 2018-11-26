#include "Tower.h"

double Tower::jarak(Monster * monsterNear)
{
	double res = sqrt(pow(x - monsterNear->getX(),2) + pow(y - monsterNear->getY(),2));
	return res;
}

Tower::Tower(int x, int y, vector<Monster*> *allMonster, vector<Bullet*> *allBullet)
{
	this->attackPoint = 10;
	this->x = x;
	this->y = y;
	this->radius = 100;
	level = 1;
	this->allMonster = allMonster;
	this->allBullet = allBullet;
}


Tower::~Tower()
{
}
