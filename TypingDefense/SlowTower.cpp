#include "SlowTower.h"

BEGIN_EVENT_TABLE(SlowTower, wxEvtHandler)
	EVT_TIMER(-1, SlowTower::slow)
END_EVENT_TABLE()

void SlowTower::slow(wxTimerEvent &event)
{
	if (!(*allMonster).empty()) {
		for (auto it : (*allMonster)) {
			if (jarak(it) <= radius) {
				it->setSlow(30);
				if (it->getStunStatus()) it->setSlow(100);
			}
			else {
				it->setSlow(0);
			}
		}
	}
}

void SlowTower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(0, 0, 255)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->radius);
}

SlowTower::SlowTower(int x, int y, vector<Monster*> &allMonster) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(10);
}


SlowTower::~SlowTower()
{
	delete timer;
}
