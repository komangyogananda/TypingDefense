#pragma once
#include "UserButton.h"

class StunTower;

class StunButton :
	public UserButton
{
private:
	StunTower *tower;
	Tower* fix;
	std::vector<wxBitmap*> *bmp;

public:
	StunButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill, std::vector<wxBitmap*> *bmp);
	~StunButton();
	void execute();
	void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse);
};