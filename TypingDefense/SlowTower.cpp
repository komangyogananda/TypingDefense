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

SlowTower::SlowTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp) : Tower(x, y, &allMonster, bmp)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(10);
	this->r = 0;
	this->g = 0;
	this->b = 255;
	this->setGambar();
}

SlowTower::SlowTower(double x, double y, vector<wxBitmap*> *bmp) : Tower(x, y, nullptr, bmp)
{
	this->timer = new wxTimer(this, -1);
	this->r = 0;
	this->g = 0;
	this->b = 255;
	this->setGambar();
}


SlowTower::~SlowTower()
{
	delete timer;
}
