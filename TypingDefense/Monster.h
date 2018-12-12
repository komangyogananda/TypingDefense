#pragma once
#include <wx/dcbuffer.h>
#include <wx/wx.h>
#include <vector>
#include <list>
#include "wx/graphics.h"

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
	double x, y;
	double targetX, targetY;
	double vx, vy, v = 1.5;
	int slow;
	int r = 20;
	void moveX(double point);
	void moveY(double point);
	void followTarget();
	int idx = 0;
	MapGame *map;
	wxTimer *timer;
	wxTimer *animationTimer;
	vector<Tower*> tauntTower;
	vector<Tower*> stunTower;
	void OnTimer(wxTimerEvent &event);
	void AnimationTimer(wxTimerEvent &event);
	bool tauntStatus = false;
	bool stunStatus = false;
	DECLARE_EVENT_TABLE()

	friend class MapGame;
public:
	Monster(MapGame *mapGame, int maxHealthPoint, int attackPoint, int x, int y, int targetX, int targetY, int level);
	~Monster();
	bool attack();
	void jalan();
	int draw(wxBufferedPaintDC &pdc, vector<wxBitmap*> *anitmation);
	bool mati();
	double getX();
	double getY();
	int getRadius();
	double getSpeed;
	void getDamage(int damage);
	void setSlow(int slow);
	void setTarget(double x, double y);
	void tauntedBy(Tower* taunt);
	void stunnedBy(Tower* stun);
	bool checkTaunt(Tower* taunt);
	bool checkStun(Tower* stun);
	bool getTauntStatus();
	bool getStunStatus();
};
