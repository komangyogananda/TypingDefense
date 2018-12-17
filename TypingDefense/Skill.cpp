#include "Skill.h"


Skill::Skill(int x, int y, vector<Monster*> *allMonster)
{
	this->centerX = x;
	this->centerY = y;
	this->allMonster = allMonster;
}

int Skill::getCenterX()
{
	return centerX;
}

int Skill::getCenterY()
{
	return centerY;
}

void Skill::setCenterX(int x)
{
	this->centerX = x;
}

void Skill::setCenterY(int y)
{
	this->centerY = y;
}

Skill::~Skill()
{
}
