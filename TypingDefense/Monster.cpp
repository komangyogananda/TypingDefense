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
	this->healthPoint = maxHealthPoint-70;
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
	pdc.DrawCircle(wxPoint(x, y), r);
	pdc.SetBrush(wxBrush(wxTransparentColour, wxBRUSHSTYLE_TRANSPARENT));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawRectangle(x - 20, y + 20, 2*r, 5);
	pdc.SetBrush(wxBrush(wxColour(255*(maxHealthPoint - healthPoint)/maxHealthPoint, 255*healthPoint/maxHealthPoint, 0), wxBRUSHSTYLE_SOLID));
	pdc.DrawRectangle(x - 20, y + 20, healthPoint*2*r/maxHealthPoint, 5);
}

Monster::~Monster()
{
}
