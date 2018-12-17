#include "Snow.h"
#include <algorithm>

BEGIN_EVENT_TABLE(Snow, wxEvtHandler)
	EVT_TIMER(2000, Snow::OnDraw)
END_EVENT_TABLE()

int Snow::getIdx()
{
	return idx;
}

void Snow::active(wxBufferedPaintDC &pdc, std::vector<wxBitmap*>* png)
{
	int i = this->centerX - 150;
	int j = this->centerY - 150;
	pdc.DrawBitmap(*(*png)[0], wxPoint(i, j));

	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			int x = it->getX();
			int y = it->getY();
			double dist = ((x - this->centerX) * (x - this->centerX) + (y - this->centerY) * (y - this->centerY));
			if (dist <= 150 * 150) {
				it->setSlow(max(it->getSlow(), 50));
			}
			else if (it->getSlow() == 50) {
				it->setSlow(0);
			}
		}
	}
}

void Snow::setIdx(int idx)
{
	this->idx = idx;
}

Snow::Snow(int x, int y) : Skill(x, y, nullptr)
{
	timer = new wxTimer(this, 2000);
	timer->Start(200);
}

Snow::Snow(int x, int y, vector<Monster*>* allMonster) : Skill(x, y, allMonster)
{
	timer = new wxTimer(this, 2000);
	timer->Start(200);
}

void Snow::OnDraw(wxTimerEvent & event)
{
	this->idx++;
}



Snow::~Snow()
{
	int i = this->centerX - 150;
	int j = this->centerY - 150;

	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			int x = it->getX();
			int y = it->getY();
			double dist = ((x - this->centerX) * (x - this->centerX) + (y - this->centerY) * (y - this->centerY));
			if (dist <= 150 * 150) {
				it->setSlow(0);
			}
		}
	}
	delete timer;
}
