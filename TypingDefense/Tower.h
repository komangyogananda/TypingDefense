#pragma once
#include "wx/dcbuffer.h"
#include "Monster.h"
#include "Bullet.h"
#include "wx/event.h"
#include <vector>
#include <math.h>

using namespace std;

class Tower : public wxEvtHandler
{
protected:
	int attackPoint, radius, level;
	int drawRadius;
	int plus = 2;
	int x, y, s;
	int r, g, b;
	vector<Monster*> *allMonster;
	double jarak(Monster* monsterNear);
	bool active;

public:
	Tower(int x, int y, vector<Monster*> *allMonster);
	~Tower();
	void draw(wxBufferedPaintDC &pdc);
	void drawPlaceholder(wxBufferedPaintDC &pdc);
	void setX(int x);
	void setY(int y);
	virtual void skill(wxTimerEvent &event) = 0;
};

