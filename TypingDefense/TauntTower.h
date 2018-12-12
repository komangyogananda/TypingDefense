#pragma once
#include "Tower.h"

class TauntTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	TauntTower(double x, double y, vector<Monster*> &allMonster);
	TauntTower(double x, double y);
	~TauntTower();
	void skill(wxTimerEvent &event);
};

