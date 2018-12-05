#pragma once
#include "UserButton.h"

class SlowTower;

class SlowButton :
	public UserButton
{
private:
	SlowTower *tower;
	Tower* fix;

public:
	SlowButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet);
	~SlowButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};

