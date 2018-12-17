#include "WallButton.h"
#include "Wall.h"
#include "MapGame.h"
#include <random>
#include <chrono>
#include <functional>

WallButton::~WallButton()
{
	delete skill;
}

WallButton::WallButton(MapGame * map, std::vector<Tower*>* allTower, std::vector<Monster*>* allMonster, std::vector<Bullet*>* allBullet, std::vector<Skill*>* allSkill)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->skill = new Wall(1, 1, 1, 1);
}



void WallButton::execute()
{
	int x = skill->getCenterX();
	int y = skill->getCenterY() - 250;
	int limY = y + 600;
	for (int j = y; j < limY; j += 100) {
		fix = new Wall(x, j, y - 50, y + 550, allMonster);
		allSkill->push_back(fix);
	}
}

void WallButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState & mouse)
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
				gc->SetBrush(wxColor(255, 255, 255, 128));
				wxGraphicsPath path = gc->CreatePath();
				path.AddRectangle(x - 25.0, y - 300.0, 50.0, 600.0);
				gc->FillPath(path);
				gc->StrokePath(path);
				delete gc;
			}
			//pdc.DrawRectangle(wxPoint(x - 150, y - 150), wxSize(300, 300));
		}
	}
}
