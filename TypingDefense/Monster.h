#pragma once
#include <wx/dcbuffer.h>
#include <wx/wx.h>
#include <vector>

using namespace std;

class MapGame;
class Tower;

class Monster : wxEvtHandler
{
private:
	int healthPoint;
	int maxHealthPoint;
	int attackPoint;
	int level;
	int x, y;
	int targetX, targetY;
	int vx, vy, v = 2;
	int slow;
	int r = 20;
	void moveX(int point);
	void moveY(int point);
	void followTarget();
	MapGame *map;
	wxTimer *timer;
	vector<Tower*> tauntTower;
	vector<Tower*> stunTower;
	void OnTimer(wxTimerEvent &event);
	bool tauntStatus = false;
	bool stunStatus = false;
	DECLARE_EVENT_TABLE()

	friend class MapGame;
public:
	Monster(MapGame *mapGame, int maxHealthPoint, int attackPoint, int x, int y, int targetX, int targetY, int level);
	~Monster();
	bool attack();
	void jalan();
	int draw(wxBufferedPaintDC &pdc);
	bool mati();
	int getX();
	int getY();
	int getRadius();
	int getSpeed;
	void getDamage(int damage);
	void setSlow(int slow);
	void setTarget(int x, int y);
	void tauntedBy(Tower* taunt);
	void stunnedBy(Tower* stun);
	bool checkTaunt(Tower* taunt);
	bool checkStun(Tower* stun);
	bool getTauntStatus();
	bool getStunStatus();
};
