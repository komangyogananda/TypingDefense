#include "Level.h"


double Level::getTime()
{
	return 6+pow(0.3, -2+this->level);
}

Level::Level(int level)
{
	this->level = level;
	this->timePerMonster = getTime();
	this->totalMonster = 6 * this->level;
	launchedMonster = 0;
	diedMonster = 0;
}

int Level::getTotalMonster()
{
	return totalMonster;
}

int Level::getLaunchedMonster()
{
	return launchedMonster;
}

int Level::getDiedMonster()
{
	return diedMonster;
}

void Level::setDiedMonster(int monster)
{
	this->diedMonster = monster;
}

double Level::getTimePerMonster()
{
	return timePerMonster;
}

double Level::getLevel()
{
	return level;
}

void Level::setLaunchedMonster(int monster)
{
	this->launchedMonster = monster;
}

Level::~Level()
{
}
