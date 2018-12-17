#pragma once
#include "Tower.h"

class StunTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	StunTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp);
	StunTower(double x, double y, vector<wxBitmap*> *bmp);
	~StunTower();
	void skill(wxTimerEvent &event);
};

