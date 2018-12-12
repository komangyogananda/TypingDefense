#pragma once
#include "Tower.h"

class StunTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	StunTower(double x, double y, vector<Monster*> &allMonster);
	StunTower(double x, double y);
	~StunTower();
	void skill(wxTimerEvent &event);
};

