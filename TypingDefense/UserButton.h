#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "vector"

class MapGame;
class Monster;
class Bullet;
class Tower;
class Skill;

class UserButton
{
protected:
	MapGame *map;
	std::vector<Tower*> *allTower;
	std::vector<Monster*> *allMonster;
	std::vector<Bullet*> *allBullet;
	std::vector<Skill*> *allSkill;

public:
	UserButton(MapGame *map, std::vector<Tower*> *allTower, std::vector<Monster*> *allMonster, std::vector<Bullet*> *allBullet, std::vector<Skill*> *allSkill);
	~UserButton();
	virtual void execute() = 0;
	virtual void drawPlaceholder(wxBufferedPaintDC &pdc, wxMouseState &mouse) = 0;
};

