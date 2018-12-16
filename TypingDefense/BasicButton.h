#pragma once
#include "UserButton.h"

class BasicTower;

class BasicButton :
	public UserButton
{
private:
	BasicTower *tower;
	Tower* fix;

public:
	BasicButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill);
	~BasicButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};

