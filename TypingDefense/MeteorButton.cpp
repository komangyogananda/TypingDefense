#pragma once
#include "MeteorButton.h"
#include "Meteor.h"
#include "MapGame.h"


MeteorButton::MeteorButton(MapGame * map, std::vector<Tower*>* allTower, std::vector<Monster*>* allMonster, std::vector<Bullet*>* allBullet, std::vector<Skill*> *allSkill)
	: UserButton(map, allTower, allMonster, allBullet, allSkill)
{
	this->skill = new Meteor(1, 1);
}

MeteorButton::~MeteorButton()
{
}

void MeteorButton::execute()
{
	fix = new Meteor(skill->getCenterX(), skill->getCenterY(), allMonster);
	allSkill->push_back(fix);
}

void MeteorButton::drawPlaceholder(wxBufferedPaintDC & pdc, wxMouseState & mouse)
{
}
