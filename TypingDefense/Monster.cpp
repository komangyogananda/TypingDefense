#include "Monster.h"
#include "MapGame.h"

Monster::~Monster()
{
}

void Monster::moveX(int point)
{
	this->x += point;
}

void Monster::moveY(int point)
{
	this->y += point;
}

Monster::Monster(MapGame *mapGame, int maxHealthPoint, int attackPoint, int x, int y, int level)
{
	map = mapGame;
	this->maxHealthPoint = maxHealthPoint;
	this->healthPoint = maxHealthPoint;
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

int Monster::draw(wxBufferedPaintDC &pdc) {
	if (mati()) return 0;
	if (attack()) return attackPoint;
	pdc.SetBrush(wxBrush(wxColour(255,255,255)));
	pdc.DrawCircle(wxPoint(x, y), r);
	pdc.SetBrush(wxBrush(wxTransparentColour, wxBRUSHSTYLE_TRANSPARENT));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawRectangle(x - 20, y + 20, 2*r, 5);
	pdc.SetBrush(wxBrush(wxColour(255*(maxHealthPoint - healthPoint)/maxHealthPoint, 255*healthPoint/maxHealthPoint, 0), wxBRUSHSTYLE_SOLID));
	pdc.DrawRectangle(x - 20, y + 20, healthPoint*2*r/maxHealthPoint, 5);
	return -1;
}

bool Monster::mati()
{
	if (healthPoint <= 0) {
		return true;
	}
	return false;
}

int Monster::getX()
{
	return x;
}

int Monster::getY()
{
	return y;
}

int Monster::getRadius()
{
	return r;
}

void Monster::getDamage(int damage)
{
	this->healthPoint -= damage;
	if (this->healthPoint < 0) this->healthPoint = 0;
}

bool Monster::attack() {
	int x;
	map->GetSize(&x, NULL);
	if (this->x >= x) return true;
	return false;
}
