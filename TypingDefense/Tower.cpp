#include "Tower.h"

double Tower::jarak(Monster * monsterNear)
{
	double res = sqrt(pow(x - monsterNear->getX(),2) + pow(y - monsterNear->getY(),2));
	return res;
}

Tower::Tower(int x, int y, vector<Monster*> *allMonster)
{
	this->attackPoint = 10;
	this->x = x;
	this->y = y;
	this->radius = 170;
	this->s = 30;
	level = 1;
	this->allMonster = allMonster;
	this->drawRadius = 1;
	this->active = false;
}


Tower::~Tower()
{
}

void Tower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(r, g, b)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->drawRadius);
	if (this->drawRadius >= this->radius || this->drawRadius <= 0) {
		plus *= -1;
	}
	this->drawRadius += plus;
	this->active = true;
}

void Tower::drawPlaceholder(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(r, g, b)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	this->active = false;
}

void Tower::setX(int x)
{
	this->x = x;
}

void Tower::setY(int y)
{
	this->y = y;
}
