#pragma once
#include "UserButton.h"

class SlowTower;

class SlowButton :
	public UserButton
{
private:
	SlowTower *tower;
	Tower* fix;
	std::vector<wxBitmap*> *bmp;

public:
	SlowButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp);
	~SlowButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};

