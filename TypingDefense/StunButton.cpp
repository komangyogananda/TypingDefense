#pragma once
#include "StunButton.h"
#include "StunTower.h"
#include "MapGame.h"

StunButton::StunButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->tower = new StunTower(1, 1);
}


StunButton::~StunButton()
{
	delete tower;
}

void StunButton::execute()
{
	fix = new StunTower(tower->getX(), tower->getY(), *allMonster);
	allTower->push_back(fix);
	this->map->getUser()->setMoney(this->map->getUser()->getMoney() - 100);
}

void StunButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState &mouse)
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
