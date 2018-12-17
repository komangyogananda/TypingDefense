#pragma once
#include "Skill.h"

class Wall
	: public Skill
{
private:
	int idx = 0;
	wxTimer *timer;
	DECLARE_EVENT_TABLE()

public:
	int getIdx();
	void active(wxBufferedPaintDC&, vector<wxBitmap*> *png);
	void setIdx(int);
	Wall(int x, int y);
	Wall(int x, int y, vector<Monster*> *allMonster);
	void OnDraw(wxTimerEvent& event);
	~Wall();
};

