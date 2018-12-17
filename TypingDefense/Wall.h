#pragma once
#include "Skill.h"

class Wall
	: public Skill
{
private:
	int upY;
	int downY;
	int idx = 0;
	wxTimer *timer;
	DECLARE_EVENT_TABLE()

public:
	int getIdx();
	void active(wxBufferedPaintDC&, vector<wxBitmap*> *png);
	void setIdx(int);
	Wall(int x, int y, int up, int down);
	Wall(int x, int y, int up, int down, vector<Monster*> *allMonster);
	void OnDraw(wxTimerEvent& event);
	~Wall();
};

