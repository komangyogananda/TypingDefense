#include "Bullet.h"


Bullet::Bullet(Monster *targetMonster, int x, int y, int damageGiven)
{
	this->x = x;
	this->y = y;
	this->targetMonster = targetMonster;
	r = 2;
	this->damageGiven = damageGiven;
	this->v = 5;
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
	pdc.SetBrush(wxBrush(wxColour(*wxBLACK)));
	pdc.DrawCircle(x, y, r);
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
