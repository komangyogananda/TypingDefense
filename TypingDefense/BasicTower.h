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
	BasicTower(double x, double y, vector<Monster*> &allMonster, vector<Bullet*> &allBullet, vector<wxBitmap*> *bmp);
	BasicTower(double x, double y, vector<wxBitmap*> *bmp);
	~BasicTower();
	void skill(wxTimerEvent &event);
};

