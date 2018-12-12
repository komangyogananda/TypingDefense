#pragma once
#include "Monster.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"
#include <math.h>

class Bullet
{
private:
	double x, y;
	int r = 4;
	double v, vx, vy;
	int damageGiven;
	Monster *targetMonster;
public:
	Bullet(Monster *targetMonster, double x, double y, int damageGiven);
	void followTarget();
	bool checkCollision();
	void draw(wxBufferedPaintDC &pdc);
	void giveDamage();
	~Bullet();
	Monster* getTargetMonster();
};

