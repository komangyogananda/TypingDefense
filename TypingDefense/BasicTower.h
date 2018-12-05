#pragma once
#include "Tower.h"

class BasicTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	Bullet* bullet;
	wxTimer *timer;
	vector<Bullet*> *allBullet;
	Monster *focusedMonster = nullptr;

public:
	BasicTower(int x, int y, vector<Monster*> &allMonster, vector<Bullet*> &allBullet);
	BasicTower(int x, int y);
	~BasicTower();
	void skill(wxTimerEvent &event);
};

