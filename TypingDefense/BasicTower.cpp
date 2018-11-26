#include "BasicTower.h"

BEGIN_EVENT_TABLE(BasicTower, wxEvtHandler)
	EVT_TIMER(-1, BasicTower::attack)
END_EVENT_TABLE()

void BasicTower::attack(wxTimerEvent &event)
{
	if (focusedMonster == nullptr && !(*allMonster).empty()) {
		if (jarak((*allMonster)[0]) <= radius) {
			focusedMonster = (*allMonster)[0];
		}
		else {
			focusedMonster = nullptr;
		}
	}else if (focusedMonster != nullptr && jarak(focusedMonster) - focusedMonster->getRadius() > radius) {
		focusedMonster = nullptr;
	}
	if (focusedMonster != nullptr) {
		bullet = new Bullet(focusedMonster, this->x, this->y, this->attackPoint);
		(*allBullet).push_back(bullet);
	}
}

void BasicTower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(0, 0, 255)));
	pdc.DrawRectangle(wxPoint(x, y), wxSize(radius/2,radius/2));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x + radius / 4, y + radius / 4), this->radius);
}

BasicTower::BasicTower(int x, int y, vector<Monster*> &allMonster, vector<Bullet*> &allBullet) : Tower(x, y, &allMonster, &allBullet)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
}


BasicTower::~BasicTower()
{
	delete timer;
}
