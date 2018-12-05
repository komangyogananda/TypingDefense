#include "SlowTower.h"

BEGIN_EVENT_TABLE(SlowTower, wxEvtHandler)
	EVT_TIMER(-1, SlowTower::skill)
END_EVENT_TABLE()

void SlowTower::skill(wxTimerEvent &event)
{
	if (this->active) {
		if (!(*allMonster).empty()) {
			for (auto it : (*allMonster)) {
				if (jarak(it) <= radius) {
					it->setSlow(30);
				}
				else {
					it->setSlow(0);
				}
				if (it->getStunStatus()) it->setSlow(100);
			}
		}
	}
}

SlowTower::SlowTower(int x, int y, vector<Monster*> &allMonster) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(10);
	this->r = 0;
	this->g = 0;
	this->b = 255;
}

SlowTower::SlowTower(int x, int y) : Tower(x, y, nullptr)
{
	this->timer = new wxTimer(this, -1);
	this->r = 0;
	this->g = 0;
	this->b = 255;
}


SlowTower::~SlowTower()
{
	delete timer;
}
