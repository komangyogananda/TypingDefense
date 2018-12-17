#pragma once
#include "Skill.h"

class Snow
	: public Skill
{
private:
	int idx;
	wxTimer *timer;
	DECLARE_EVENT_TABLE()

public:
	
	int getIdx();
	void active(wxBufferedPaintDC&, vector<wxBitmap*> *png);
	void setIdx(int);
	Snow(int x, int y);
	Snow(int x, int y, vector<Monster*> *allMonster);
	void OnDraw(wxTimerEvent& event);
	~Snow();
};

