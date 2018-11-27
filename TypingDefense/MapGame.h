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

using namespace std;

struct koordinatBox {
	int x1, y1, x2, y2;
};

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int w, h;
	wxFrame* parent;
	wxBitmap* background, *coin, *questClock, *questImage1, *questImage2, *questImage3;
	wxSize coinSize;
	wxImage image;
	wxButton *backToMainMenu;
	wxStatusBar *mapStatusBar;
	wxImage loadLogo(wxString path);
	vector<koordinatBox> skillButton;
	vector<Monster*> allMonster;
	vector<wxBitmap*> skill;
	vector<Bullet*> allBullet;
	wxTimer *timer;
	wxTimer *questTimer;
	string status;
	User *user;
	void drawHealthBar(wxBufferedPaintDC &pdc);
	Quest *quest;
	clock_t now = clock();
	clock_t statusTimer;
	int questInterval;
	vector<Tower*> allTower;
	void changeWindow();

public:
	MapGame(wxFrame *parent);
	~MapGame();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnKeyDown(wxKeyEvent &event);
	void OnChar(wxKeyEvent &event);
	void QuestGiver(wxTimerEvent &event);
};

