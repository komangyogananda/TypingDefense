#pragma once
#include "UserButton.h"

class Meteor;

class MeteorButton :
	public UserButton
{
private:
	Meteor *skill;
	Skill* fix;

public:
	MeteorButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill);
	~MeteorButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};