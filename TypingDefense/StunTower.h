#pragma once
#include "Tower.h"

class StunTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	StunTower(int x, int y, vector<Monster*> &allMonster);
	~StunTower();
	void skill(wxTimerEvent &event);
};

