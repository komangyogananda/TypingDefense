#pragma once
#include "Tower.h"

class SlowTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	SlowTower(double x, double y, vector<Monster*> &allMonster);
	SlowTower(double x, double y);
	~SlowTower();
	void skill(wxTimerEvent &event);
};

