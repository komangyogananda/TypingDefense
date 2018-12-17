#pragma once
#include "UserButton.h"

class Snow;

class SnowButton
	: public UserButton
{
private:
	Snow *skill;
	Skill* fix;

public:
	SnowButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill);
	~SnowButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};

