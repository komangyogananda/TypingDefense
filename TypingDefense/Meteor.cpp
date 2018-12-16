#include "Meteor.h"

BEGIN_EVENT_TABLE(Meteor, wxEvtHandler)
	EVT_TIMER(2000, Meteor::OnDraw)
END_EVENT_TABLE()

Meteor::~Meteor()
{
	delete timer;
}

void Meteor::active(wxBufferedPaintDC &pdc, vector<wxBitmap*> * png)
{
	if (idx < 0) {
		idx++;
	}
	else {
		pdc.DrawBitmap(*(*png)[idx], wxPoint(this->centerX, this->centerY));
		if (!(*allMonster).empty()) {
			for (auto it : *allMonster) {
				double dist = sqrt((this->centerX - it->getX()) * (this->centerX - it->getX()) + (this->centerY - it->getY()) * (this->centerY - it->getY()));
				if (dist <= this->radius) {
					it->getDamage(this->damage);
				}
			}
		}
	}
	
}

Meteor::Meteor(int x, int y, vector<Monster*> *allMonster) : Skill(x, y, allMonster)
{
	timer = new wxTimer(this, 2000);
	timer->Start(50);
}

Meteor::Meteor(int x, int y) : Skill(x, y, nullptr)
{
	timer = new wxTimer(this, 2000);
	timer->Start(50);
}

int Meteor::getIdx()
{
	return idx;
}

void Meteor::setIdx(int idx)
{
	this->idx = idx;
}



void Meteor::OnDraw(wxTimerEvent& event)
{
	this->idx++;
}


