#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include <vector>
#include <string>
#include "Monster.h"
#include "User.h"
#include "Quest.h"

struct koordinatBox {
	int x1, y1, x2, y2;
};

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int w, h;
	wxFrame* parent;
	wxBitmap* background, *coin;
	wxSize coinSize;
	wxImage image;
	wxButton *backToMainMenu;
	wxStatusBar *mapStatusBar;
	wxImage loadLogo(wxString path);
	std::vector<koordinatBox> skillButton;
	std::vector<Monster*> allMonster;
	std::vector<wxBitmap*> skill;
	wxTimer *timer;
	wxTimer *questTimer;
	std::string status;
	User *user;
	void drawHealthBar(wxBufferedPaintDC &pdc);
	Quest *quest;
	clock_t now = clock();
	int questInterval;

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

