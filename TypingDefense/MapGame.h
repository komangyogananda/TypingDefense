#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include <vector>
#include <string>
#include "Monster.h"
#include "User.h"
#include "Quest.h"
#include "BasicTower.h"
#include "Bullet.h"
#include <list>
#include <wx/bmpbuttn.h>
#include "SlowTower.h"
#include "TauntTower.h"
#include "StunTower.h"
#include "UserButton.h"
#include "MeteorButton.h"
#include "SnowButton.h"
#include "WallButton.h"
#include "BasicButton.h"
#include "SlowButton.h"
#include "StunButton.h"
#include "TauntButton.h"
#include "Level.h"
#include "Skill.h"
#include "Meteor.h"
#include "Snow.h"
#include "Wall.h"

using namespace std;

struct koordinatBox {
	int x1, y1, x2, y2;
};

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int w, h, coinIdx = 0;
	int minusHealth = 0;
	wxFrame* parent;
	wxBitmap* background, *questClock, *questImage1, *questImage2, *questImage3;
	wxBitmap* nocoin;
	wxSize coinSize;
	wxImage image;
	Tower *tower, *placeholder;
	Skill *curSkill;
	wxImage loadLogo(wxString path);
	vector<koordinatBox> skillButton;
	vector<Monster*> allMonster;
	vector<wxBitmap*> skill, animationMonster, coin, meteorPng, snowPng, wallPng;
	vector<Bullet*> allBullet;
	wxTimer *timer;
	wxTimer *questTimer;
	wxTimer *spawnTimer;
	int timerInterval, questTimerInterval, spawnTimerInterval;
	User *user;
	void drawHealthBar(wxBufferedPaintDC &pdc);
	void drawPlaceholderTower(wxBufferedPaintDC &pdc);
	Quest *quest;
	clock_t now = clock();
	clock_t statusTimer;
	clock_t cooldownTimer;
	clock_t meteorCD, snowCD, wallCD;
	int questInterval;
	vector<Tower*> allTower;
	vector<Skill*> allSkill;
	void changeWindow();
	int randNum(int low, int high);
	UserButton *activeButton;
	MeteorButton *meteorButton;
	SnowButton *snowButton;
	WallButton *wallButton;
	BasicButton *basicButton;
	SlowButton *slowButton;
	StunButton *stunButton;
	TauntButton *tauntButton;
	bool nocoinstatus = false;
	wxTimer *nocointimer;
	int nocointimerInterval;
	Level *level;
	wxBitmap *questBackground;
	wxBitmap *pauseBar;
	bool pause = false;
	vector<wxBitmap*> towerImage;
	wxBitmap* levelUpImage;
	wxBitmap* waveIncoming;
	bool drawLevelUpImage = false;
	bool drawWaveImage = false;

public:
	MapGame(wxFrame *parent, User* user);
	~MapGame();
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	void OnChar(wxKeyEvent &event);
	void QuestGiver(wxTimerEvent &event);
	void NoCoin(wxTimerEvent &event);
	void SpawnMonster(wxTimerEvent &event);
	void animationMinusHealthBar();
	void LevelUp();
	void pauseGame();
	void resumeGame();
	void drawCooldown(wxBufferedPaintDC&);
	User* getUser();
};

