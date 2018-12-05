#pragma once
#include "Monster.h"
#include "wx/dcbuffer.h"
#include <math.h>

class Bullet
{
private:
	int x, y, r = 2;
	int v, vx, vy;
	int damageGiven;
	Monster *targetMonster;
public:
	Bullet(Monster *targetMonster, int x, int y, int damageGiven);
	void followTarget();
	bool checkCollision();
	void draw(wxBufferedPaintDC &pdc);
	void giveDamage();
	~Bullet();
	Monster* getTargetMonster();
};

