#pragma once
#include "MeteorButton.h"
#include "Meteor.h"
#include "MapGame.h"
#include <random>
#include <chrono>
#include <functional>

MeteorButton::MeteorButton(MapGame * map, std::vector<Tower*>* allTower, std::vector<Monster*>* allMonster, std::vector<Bullet*>* allBullet, std::vector<Skill*> *allSkill)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->skill = new Meteor(1, 1);
}

MeteorButton::~MeteorButton()
{
	delete skill;
}

void MeteorButton::execute()
{
	for (int i = 0; i < 15; i++) {
		std::mt19937 rng;
		rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<std::mt19937::result_type> dist(i, i + 3);
		std::uniform_int_distribution<std::mt19937::result_type> distX(0, map->GetSize().GetX());
		std::uniform_int_distribution<std::mt19937::result_type> distY(0, map->GetSize().GetY());

		int t = (dist(rng));
		int x = (distX(rng));
		int y = (distY(rng));
		wxMessageOutputDebug().Printf("%d %d", x, y);
		fix = new Meteor(x, y, allMonster);
		fix->setIdx(-t);
		allSkill->push_back(fix);
	}
}

void MeteorButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState & mouse)
{
}
