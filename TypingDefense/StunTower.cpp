#include "StunTower.h"

BEGIN_EVENT_TABLE(StunTower, wxEvtHandler)
	EVT_TIMER(-1, StunTower::skill)
END_EVENT_TABLE()

void StunTower::skill(wxTimerEvent &event)
{
	if (this->active) {
		if (!(*allMonster).empty()) {
			for (auto it : (*allMonster)) {
				if (jarak(it) <= radius && !it->getStunStatus() && it->checkStun(this)) {
					it->setSlow(100);
					it->stunnedBy(this);
				}
				else if (it->getStunStatus()) {
					continue;
				}
				else {
					it->setSlow(0);
				}
			}
		}
	}
}

StunTower::StunTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp) : Tower(x, y, &allMonster, bmp)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->setGambar();
}

StunTower::StunTower(double x, double y, vector<wxBitmap*> *bmp) : Tower(x, y, nullptr, bmp)
{
	this->timer = new wxTimer(this, -1);
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->setGambar();
}

StunTower::~StunTower()
{
	delete timer;
}
