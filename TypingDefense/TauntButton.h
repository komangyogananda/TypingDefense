#pragma once
#include "UserButton.h"

class TauntTower;

class TauntButton :
	public UserButton
{
private:
	TauntTower *tower;
	Tower* fix;
	std::vector<wxBitmap*> *bmp;

public:
	TauntButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp);
	~TauntButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};