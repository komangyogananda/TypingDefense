#pragma once
#include <math.h>

class Level
{
private:
	int level;
	double timePerMonster;
	int totalMonster;
	int launchedMonster;
	int diedMonster;
	double getTime();
public:
	Level(int level);
	int getTotalMonster();
	int getLaunchedMonster();
	int getDiedMonster();
	void setDiedMonster(int monster);
	double getTimePerMonster();
	double getLevel();
	void setLaunchedMonster(int monster);
	~Level();
};

