#pragma once
#include "UserButton.h"

class StunTower;

class StunButton :
	public UserButton
{
private:
	StunTower *tower;
	Tower* fix;

public:
	StunButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet);
	~StunButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};