#pragma once
#include <math.h>

class Level
{
private:
	int level;
	double timePerMonster;
	int totalMonster;
	int launchedMonster;
	double getTime();
public:
	Level(int level);
	int getTotalMonster();
	int getLaunchedMonster();
	double getTimePerMonster();
	double getLevel();
	void setLaunchedMonster(int monster);
	~Level();
};

