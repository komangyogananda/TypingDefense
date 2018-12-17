#pragma once
#include "TauntButton.h"
#include "TauntTower.h"
#include "MapGame.h"

TauntButton::TauntButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->bmp = bmp;
	this->tower = new TauntTower(1, 1, bmp);
}


TauntButton::~TauntButton()
{
	delete tower;
}

void TauntButton::execute()
{
	fix = new TauntTower(tower->getX(), tower->getY(), *allMonster, bmp);
	allTower->push_back(fix);
	this->map->getUser()->setMoney(this->map->getUser()->getMoney() - 100);
}

void TauntButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState &mouse)
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
