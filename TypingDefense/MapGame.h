#pragma once
#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include <vector>
#include <string>
#include "Monster.h"
#include "User.h"

struct koordinatBox {
	int x1, y1, x2, y2;
};

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int w, h;
	wxFrame* parent;
	wxBitmap* background;
	wxImage image;
	wxButton *backToMainMenu;
	wxStatusBar *mapStatusBar;
	wxImage loadLogo(wxString path);
	std::vector<koordinatBox> skillButton;
	std::vector<Monster*> allMonster;
	std::vector<wxBitmap*> skill;
	wxTimer *timer;
	std::string status;
	User *user;
	void drawHealthBar(wxBufferedPaintDC &pdc);

public:
	MapGame(wxFrame *parent);
	~MapGame();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
};

