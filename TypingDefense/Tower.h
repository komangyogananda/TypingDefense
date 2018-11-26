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
	int x, y;
	Monster *focusedMonster = nullptr;
	vector<Monster*> *allMonster;
	vector<Bullet*> *allBullet;
	double jarak(Monster* monsterNear);
public:
	Tower(int x, int y, vector<Monster*> *allMonster, vector<Bullet*> *allBullet);
	~Tower();
	virtual void draw(wxBufferedPaintDC &pdc) = 0;
};

