#pragma once
#include "wx/dcbuffer.h"
#include "Monster.h"
#include "Bullet.h"
#include "wx/event.h"
#include <vector>
#include <math.h>

class Skill
	: public wxEvtHandler
{
protected:
	vector<Monster*> *allMonster;
	int cooldown;
	int centerX, centerY;
public:
	virtual void active(wxBufferedPaintDC&, vector<wxBitmap*> *png) = 0;
	Skill(int x, int y, vector<Monster*> *allMonster);
	int getCenterX();
	int getCenterY();
	~Skill();
};

