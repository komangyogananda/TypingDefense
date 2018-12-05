#include "UserButton.h"
#include "MapGame.h"

UserButton::UserButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet)
{
	this->map = map;
	this->allTower = allTower;
	this->allMonster = allMonster;
	this->allBullet = allBullet;
}

UserButton::~UserButton()
{
}
