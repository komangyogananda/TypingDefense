#include "BasicTower.h"

BEGIN_EVENT_TABLE(BasicTower, wxEvtHandler)
	EVT_TIMER(-1, BasicTower::skill)
END_EVENT_TABLE()

void BasicTower::skill(wxTimerEvent &event)
{
	if (this->active) {
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
}

BasicTower::BasicTower(double x, double y, vector<Monster*> &allMonster, vector<Bullet*> &allBullet) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
	this->allBullet = &allBullet;
	this->r = 255;
	this->g = 0;
	this->b = 0;
}

BasicTower::BasicTower(double x, double y) : Tower(x, y, nullptr)
{
	this->timer = new wxTimer(this, -1);
	this->allBullet = nullptr;
	this->r = 255;
	this->g = 0;
	this->b = 0;
}


BasicTower::~BasicTower()
{
	delete timer;
}
