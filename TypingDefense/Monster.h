#pragma once
#include <wx/dcbuffer.h>
#include <wx/wx.h>

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

	friend class MapGame;
public:
	Monster(int maxHealthPoint, int attackPoint, int x, int y, int level);
	void attack();
	void jalan(int x, int y);
	void draw(wxBufferedPaintDC &pdc);
	~Monster();
};
