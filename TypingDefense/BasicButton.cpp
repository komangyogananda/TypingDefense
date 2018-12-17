#pragma once
#include "BasicButton.h"
#include "BasicTower.h"
#include "MapGame.h"

BasicButton::BasicButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->bmp = bmp;
	this->tower = new BasicTower(1,1, bmp);
}


BasicButton::~BasicButton()
{
	delete tower;
}

void BasicButton::execute()
{
	fix = new BasicTower(tower->getX(), tower->getY(), *allMonster, *allBullet, this->bmp);
	allTower->push_back(fix);
	this->map->getUser()->setMoney(this->map->getUser()->getMoney() - 100);
}

void BasicButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState &mouse)
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
