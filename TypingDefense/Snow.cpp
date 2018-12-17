#include "Snow.h"

BEGIN_EVENT_TABLE(Snow, wxEvtHandler)
	EVT_TIMER(2000, Snow::OnDraw)
END_EVENT_TABLE()

int Snow::getIdx()
{
	return idx;
}

void Snow::active(wxBufferedPaintDC &pdc, std::vector<wxBitmap*>* png)
{
	int i = this->centerX;
	int j = this->centerY;
	int limX = i + 100;
	int limY = j + 100;
	pdc.DrawBitmap(*(*png)[0], wxPoint(i, j));

	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			int x = it->getX();
			int y = it->getY();
			if (i <= x && x <= limX && j <= y && y <= limY) {
				it->setSlow(50);
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
	int i = this->centerX;
	int j = this->centerY;
	int limX = i + 100;
	int limY = j + 100;
	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			int x = it->getX();
			int y = it->getY();
			if (i <= x && x <= limX && j <= y && y <= limY) {
				it->setSlow(0);
			}
		}
	}
	delete timer;
}
