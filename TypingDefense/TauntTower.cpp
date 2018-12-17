#include "TauntTower.h"

BEGIN_EVENT_TABLE(TauntTower, wxEvtHandler)
	EVT_TIMER(-1, TauntTower::skill)
END_EVENT_TABLE()

void TauntTower::skill(wxTimerEvent &event)
{
	if (this->active) {
		if (!(*allMonster).empty()) {
			for (auto it : (*allMonster)) {
				if (jarak(it) <= radius && !it->getTauntStatus() && it->checkTaunt(this) && !it->getStunStatus()) {
					it->setTarget(this->x, this->y);
					it->tauntedBy(this);
				}
				else if (it->getTauntStatus()) {
					continue;
				}
				else {
					it->setTarget(-1, -1);
				}
			}
		}
	}
}

TauntTower::TauntTower(double x, double y, vector<Monster*> &allMonster, vector<wxBitmap*> *bmp) : Tower(x, y, &allMonster, bmp)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
	this->r = 0;
	this->g = 255;
	this->b = 0;
	this->setGambar();
}

TauntTower::TauntTower(double x, double y, vector<wxBitmap*> *bmp) : Tower(x, y, nullptr, bmp)
{
	this->timer = new wxTimer(this, -1);
	this->r = 0;
	this->g = 255;
	this->b = 0;
	this->setGambar();
}


TauntTower::~TauntTower()
{
	delete timer;
}
