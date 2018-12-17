#pragma once
#include "UserButton.h"

class Wall;

class WallButton
	: public UserButton
{
private:
	Wall *skill;
	Skill* fix;

public:
	WallButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill);
	~WallButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};

