#pragma once
#include "Tower.h"

class SlowTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	SlowTower(int x, int y, vector<Monster*> &allMonster);
	SlowTower(int x, int y);
	~SlowTower();
	void skill(wxTimerEvent &event);
};

