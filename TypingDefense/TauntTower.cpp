#include "TauntTower.h"

BEGIN_EVENT_TABLE(TauntTower, wxEvtHandler)
	EVT_TIMER(-1, TauntTower::taunt)
END_EVENT_TABLE()

void TauntTower::taunt(wxTimerEvent &event)
{
	if (!(*allMonster).empty()) {
		for (auto it : (*allMonster)) {
			if (jarak(it) <= radius && !it->getTauntStatus() && it->checkTaunt(this)) {
				it->setTarget(this->x, this->y);
				it->tauntedBy(this);
			}else if (it->getTauntStatus()) {
				continue;
			}else {
				it->setTarget(-1, -1);
			}
		}
	}
}
 
void TauntTower::draw(wxBufferedPaintDC & pdc)
{
	pdc.SetBrush(wxBrush(wxColour(0, 255, 0)));
	pdc.DrawRectangle(wxPoint(x - s / 2, y - s / 2), wxSize(s, s));
	pdc.SetBrush(wxBrush(wxColour(255, 255, 255), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawCircle(wxPoint(x, y), this->radius);
}

TauntTower::TauntTower(int x, int y, vector<Monster*> &allMonster) : Tower(x, y, &allMonster)
{
	this->timer = new wxTimer(this, -1);
	timer->Start(500);
}


TauntTower::~TauntTower()
{
	delete timer;
}
