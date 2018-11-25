#include "Monster.h"

void Monster::moveX(int point)
{
	this->x += point;
}

void Monster::moveY(int point)
{
	this->y += point;
}

Monster::Monster(int maxHealthPoint, int attackPoint, int x, int y, int level)
{
	this->maxHealthPoint = maxHealthPoint;
	this->healthPoint = healthPoint;
	this->attackPoint = attackPoint;
	this->x = x;
	this->y = y;
	this->level = level;

}

void Monster::jalan(int x, int y)
{
	moveX(x);
	moveY(y);
}

void Monster::draw(wxBufferedPaintDC &pdc) {
	pdc.SetBrush(wxBrush(wxColour(255,255,255)));
	pdc.DrawCircle(wxPoint(x, y), 20);
}

Monster::~Monster()
{
}
