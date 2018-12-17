#pragma once
#include "Tower.h"

class SlowTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	SlowTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp);
	SlowTower(double x, double y, vector<wxBitmap*> *bmp);
	~SlowTower();
	void skill(wxTimerEvent &event);
};

