#include "SnowButton.h"
#include "Snow.h"
#include "MapGame.h"
#include <random>
#include <chrono>
#include <functional>


SnowButton::SnowButton(MapGame * map, std::vector<Tower*>* allTower, std::vector<Monster*>* allMonster, std::vector<Bullet*>* allBullet, std::vector<Skill*>* allSkill)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->skill = new Snow(1, 1);
}

SnowButton::~SnowButton()
{
}

void SnowButton::execute()
{
	int x = skill->getCenterX() - 150;
	int y = skill->getCenterY() - 150;
	int limX = x + 300;
	int limY = y + 300;
	for (int i = x; i < limX; i += 100) {
		for (int j = y; j < limY; j += 100) {
			fix = new Snow(i, j, allMonster);
			allSkill->push_back(fix);
		}
	}
}

void SnowButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState & mouse)
{
	if (!mouse.LeftIsDown()) {

		int x = wxGetMousePosition().x;
		int y = wxGetMousePosition().y;

		if (this->skill != nullptr) {
			skill->setCenterX(x);
			skill->setCenterY(y);
		}

		if (this->skill != nullptr) {
			wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);
			if (gc)
			{
				// make a path that contains a circle and some lines
				gc->SetPen(*wxWHITE_PEN);
				gc->SetBrush(wxColor(204, 255, 255, 128));
				wxGraphicsPath path = gc->CreatePath();
				path.AddRectangle(x - 150.0, y - 150.0, 300.0, 300.0);
				gc->FillPath(path);
				gc->StrokePath(path);
				delete gc;
			}
			//pdc.DrawRectangle(wxPoint(x - 150, y - 150), wxSize(300, 300));
		}
	}
}
