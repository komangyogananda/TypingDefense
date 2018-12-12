#include "Bullet.h"


Bullet::Bullet(Monster *targetMonster, double x, double y, int damageGiven)
{
	this->x = x;
	this->y = y;
	this->targetMonster = targetMonster;
	r = 2;
	this->damageGiven = damageGiven;
	this->v = 3.0;
	this->vx = 0;
	this->vy = 0;
}

void Bullet::followTarget()
{
	double sX = targetMonster->getX() - this->x;
	double sY = targetMonster->getY() - this->y;
	double sMiring = sqrt(pow(sX, 2) + pow(sY, 2));
	double ratio = (double)this->v / sMiring;
	double tempVx = ratio * sX;
	double tempVy = ratio * sY;
	vx = tempVx;
	vy = tempVy;
}

bool Bullet::checkCollision()
{
	followTarget();
	double jarak = sqrt(pow((targetMonster->getX() - x),2) + pow((targetMonster->getY() - y),2)) - (r/2);
	if (jarak <= targetMonster->getRadius()) return true;
	return false;
}

void Bullet::draw(wxBufferedPaintDC &pdc)
{
	x += vx;
	y += vy;
	/*pdc.SetBrush(wxBrush(wxColour(*wxBLACK)));
	pdc.DrawCircle(x, y, r);*/

	wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);
	if (gc)
	{
		// make a path that contains a circle and some lines
		gc->SetPen(*wxBLACK_PEN);
		gc->SetBrush(*wxBLACK_BRUSH);
		wxGraphicsPath path = gc->CreatePath();
		path.AddCircle(x, y, r);
		gc->FillPath(path);
		gc->StrokePath(path);
		delete gc;
	}

}

void Bullet::giveDamage()
{
	this->targetMonster->getDamage(damageGiven);
}

Bullet::~Bullet()
{
}

Monster * Bullet::getTargetMonster()
{
	return targetMonster;
}
