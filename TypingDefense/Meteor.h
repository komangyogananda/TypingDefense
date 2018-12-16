#pragma once
#include "Skill.h"

class Meteor :
	public Skill
{
private:
	int radius = 100;
	int damage = 70;
	int idx = 0;
	wxTimer *timer;
	DECLARE_EVENT_TABLE()

public:
	virtual void active(wxBufferedPaintDC&, vector<wxBitmap*> *png);
	Meteor(int x, int y, vector<Monster*> *allMonster);
	Meteor(int x, int y);
	~Meteor();
	void OnDraw(wxTimerEvent& event);
	
};

