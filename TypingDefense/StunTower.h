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
	void stun(wxTimerEvent &event);
	void draw(wxBufferedPaintDC &pdc);
};

