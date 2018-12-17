#pragma once
#include "SlowButton.h"
#include "SlowTower.h"
#include "MapGame.h"

SlowButton::SlowButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->bmp = bmp;
	this->tower = new SlowTower(1, 1, bmp);
}


SlowButton::~SlowButton()
{
	delete tower;
}

void SlowButton::execute()
{
	fix = new SlowTower(tower->getX(), tower->getY(), *allMonster, this->bmp);
	allTower->push_back(fix);
	this->map->getUser()->setMoney(this->map->getUser()->getMoney() - 100);
}

void SlowButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState &mouse)
{
	if (!mouse.LeftIsDown()) {

		int x = wxGetMousePosition().x;
		int y = wxGetMousePosition().y;

		if (this->tower != nullptr) {
			tower->setX(x);
			tower->setY(y);
		}

		if (tower != nullptr) {
			tower->drawPlaceholder(pdc);
		}
	}
}
