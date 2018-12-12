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
	double x, y, s;
	int r, g, b;
	vector<Monster*> *allMonster;
	double jarak(Monster* monsterNear);
	bool active;

public:
	Tower(double x, double y, vector<Monster*> *allMonster);
	~Tower();
	void draw(wxBufferedPaintDC &pdc);
	void drawPlaceholder(wxBufferedPaintDC &pdc);
	void setX(double x);
	void setY(double y);
	int getX();
	int getY();
	virtual void skill(wxTimerEvent &event) = 0;
};

