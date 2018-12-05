#pragma once
#include "UserButton.h"

class TauntTower;

class TauntButton :
	public UserButton
{
private:
	TauntTower *tower;
	Tower* fix;

public:
	TauntButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet);
	~TauntButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};