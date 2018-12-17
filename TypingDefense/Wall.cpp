#include "Wall.h"
#include <algorithm>
BEGIN_EVENT_TABLE(Wall, wxEvtHandler)
	EVT_TIMER(2000, Wall::OnDraw)
END_EVENT_TABLE()

Wall::Wall(int x, int y, int up, int down) : Skill(x, y, nullptr)
{
	up = upY;
	down = downY;
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
			if (i <= x && x <= limX && upY <= y && y <= downY) {
				it->setSlow(max(it->getSlow(), 100));
			}
			else if (it->getSlow() == 100)
				it->setSlow(0);
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

Wall::Wall(int x, int y, int up, int down, vector<Monster*>* allMonster)
	: Skill(x, y, allMonster)
{
	upY = up;
	downY = down;
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
			if (i <= x && x <= limX && upY <= y && y <= downY) {
				it->setSlow(0);
			}
		}
	}
	delete timer;
}
