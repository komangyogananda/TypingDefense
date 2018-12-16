#pragma once
#include "Skill.h"

class Meteor :
	public Skill
{
private:
	int radius = 100;
	int damage = 70;
	int idx;
	wxTimer *timer;
	DECLARE_EVENT_TABLE()

public:
	virtual void active(wxBufferedPaintDC&, vector<wxBitmap*> *png);
	Meteor(int x, int y, vector<Monster*> *allMonster);
	Meteor(int x, int y);
	int getIdx();
	void setIdx(int);
	~Meteor();
	void OnDraw(wxTimerEvent& event);
};

