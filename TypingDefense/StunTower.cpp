#include "StunTower.h"

BEGIN_EVENT_TABLE(StunTower, wxEvtHandler)
	EVT_TIMER(-1, StunTower::stun)
END_EVENT_TABLE()

void StunTower::stun(wxTimerEvent &event)
{
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

void StunTower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(0, 0, 0)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->radius);
}

StunTower::StunTower(int x, int y, vector<Monster*> &allMonster) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
}


StunTower::~StunTower()
{
	delete timer;
}
