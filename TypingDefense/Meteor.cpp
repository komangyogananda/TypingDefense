#include "Meteor.h"

BEGIN_EVENT_TABLE(Meteor, wxEvtHandler)
	EVT_TIMER(2000, Meteor::OnDraw)
END_EVENT_TABLE()

void Meteor::active(wxBufferedPaintDC &pdc, vector<wxBitmap*> * png)
{

	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			double dist = sqrt((this->centerX - it->getX()) * (this->centerX - it->getX()) + (this->centerY - it->getY()) * (this->centerY - it->getY()));
			if (dist <= this->radius) {
				it->getDamage(this->damage);
			}
		}
	}
}

Meteor::Meteor(int x, int y, vector<Monster*> *allMonster) : Skill(x, y, allMonster)
{
}

Meteor::Meteor(int x, int y) : Skill(x, y, nullptr)
{

}

void Meteor::OnDraw(wxTimerEvent& event)
{
	this->idx++;
}


Meteor::~Meteor()
{
}
