#include "BasicTower.h"

BEGIN_EVENT_TABLE(BasicTower, wxEvtHandler)
	EVT_TIMER(-1, BasicTower::attack)
END_EVENT_TABLE()

void BasicTower::attack(wxTimerEvent &event)
{
	if (focusedMonster != nullptr && jarak(focusedMonster) > radius) {
		focusedMonster = nullptr;
	}
	if (focusedMonster == nullptr && !(*allMonster).empty()) {
		double mn = 10000.0;
		for (auto it : (*allMonster)) {
			double curr = jarak(it);
			if (curr <= radius && curr < mn) {
				mn = jarak(it);
				focusedMonster = it;
			}
		}
	}
	if (focusedMonster != nullptr) {
		bullet = new Bullet(focusedMonster, this->x, this->y, this->attackPoint);
		(*allBullet).push_back(bullet);
	}
}

void BasicTower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(255, 0, 0)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->radius);
}

BasicTower::BasicTower(int x, int y, vector<Monster*> &allMonster, vector<Bullet*> &allBullet) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
	this->allBullet = &allBullet;
}


BasicTower::~BasicTower()
{
	delete timer;
}
