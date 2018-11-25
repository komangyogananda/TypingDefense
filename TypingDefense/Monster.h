#pragma once
#include <wx/dcbuffer.h>
#include <wx/wx.h>

class MapGame;

class Monster
{
private:
	int healthPoint;
	int maxHealthPoint;
	int attackPoint;
	int level;
	int x, y;
	int r = 20;
	void moveX(int point);
	void moveY(int point);
	MapGame *map;

	friend class MapGame;
public:
	Monster(MapGame *mapGame, int maxHealthPoint, int attackPoint, int x, int y, int level);
	~Monster();
	bool attack();
	void jalan(int x, int y);
	int draw(wxBufferedPaintDC &pdc);
	bool mati();
};
