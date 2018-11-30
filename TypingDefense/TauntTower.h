#pragma once
#include "Tower.h"

class TauntTower :
	public Tower
{
private:
	DECLARE_EVENT_TABLE()
	wxTimer *timer;

public:
	TauntTower(int x, int y, vector<Monster*> &allMonster);
	~TauntTower();
	void taunt(wxTimerEvent &event);
	void draw(wxBufferedPaintDC &pdc);
};

