#pragma once
#include "Tower.h"

class TauntTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	TauntTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp);
	TauntTower(double x, double y, vector<wxBitmap*> *bmp);
	~TauntTower();
	void skill(wxTimerEvent &event);
};

