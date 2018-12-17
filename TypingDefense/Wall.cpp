#include "Wall.h"

BEGIN_EVENT_TABLE(Wall, wxEvtHandler)
	EVT_TIMER(2000, Wall::OnDraw)
END_EVENT_TABLE()

Wall::Wall(int x, int y) : Skill(x, y, nullptr)
{
	timer = new wxTimer(this, 2000);
	timer->Start(200);
}

void Wall::active(wxBufferedPaintDC &pdc, vector<wxBitmap*>* png)
{
	int i = this->centerX;
	int j = this->centerY;
	int limX = i + 25;
	int limY = j + 50;
	i -= 25;
	j -= 50;
	pdc.DrawBitmap(*(*png)[0], wxPoint(i, j));

	if (!(*allMonster).empty()) {
		for (auto it : *allMonster) {
			int x = it->getX();
			int y = it->getY();
			if (i <= x && x <= limX && j <= y && y <= limY) {
				it->setSlow(100);
			}
		}
	}
}

int Wall::getIdx()
{
	return this->idx;
}

void Wall::setIdx(int idx)
{
	this->idx = idx;
}

Wall::Wall(int x, int y, vector<Monster*>* allMonster)
	: Skill(x, y, allMonster)
{
	timer = new wxTimer(this, 2000);
	timer->Start(200);
}

void Wall::OnDraw(wxTimerEvent & event)
{
	this->idx++;
}

Wall::~Wall()
{
	int i = this->centerX;
	int j = this->centerY;
	int limX = i + 25;
	int limY = j + 50;
	i -= 25;
	j -= 50;

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
