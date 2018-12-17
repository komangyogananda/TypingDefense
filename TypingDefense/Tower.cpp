#include "Tower.h"

double Tower::jarak(Monster * monsterNear)
{
	double res = sqrt(pow(x - monsterNear->getX(),2) + pow(y - monsterNear->getY(),2));
	return res;
}

Tower::Tower(double x, double y, vector<Monster*> *allMonster, vector<wxBitmap*> *bmp)
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
	this->bmp = bmp;
}


Tower::~Tower()
{
}

void Tower::draw(wxBufferedPaintDC & pdc)
{
	/*pdc.SetBrush(wxBrush(wxColour(r, g, b)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->drawRadius);*/

	wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);
	if (gc)
	{
		wxGraphicsPath path = gc->CreatePath();
		gc->SetPen(wxPen(wxColour(255,255,255)));
		gc->SetBrush(wxBrush(wxColour(255,255,255)));
		path.AddCircle(x, y, this->drawRadius);
		gc->StrokePath(path);
		gc->DrawBitmap(*gambar, x - 2 / 2, y - s / 2, s, s);
		delete gc;
	}

	if (this->drawRadius >= this->radius || this->drawRadius <= 0) {
		plus *= -1;
	}
	this->drawRadius += plus;
	this->active = true;
}

void Tower::drawPlaceholder(wxBufferedPaintDC & pdc)
{
	/*pdc.SetBrush(wxBrush(wxColour(r, g, b)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));*/

	wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);
	if (gc)
	{
		gc->SetPen(*wxWHITE_PEN);
		gc->SetBrush(wxBrush(wxColour(r, g, b, 120)));
		gc->DrawBitmap(*gambar, x - 2 / 2, y - s / 2, s, s);
		delete gc;
	}

	this->active = false;
}

void Tower::setX(double x)
{
	this->x = x;
}

void Tower::setY(double y)
{
	this->y = y;
}

int Tower::getX()
{
	return x;
}

int Tower::getY()
{
	return y;
}

void Tower::setGambar()
{
	int idx;
	if (r == 255) idx = 0;
	else if (b == 255) idx = 1;
	else if (g == 255) idx = 2;
	else idx = 3;
	gambar = (*bmp)[idx];
}
