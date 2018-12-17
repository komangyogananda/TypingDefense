#pragma once
#include "wx/wx.h"
#include <vector>

using namespace std;

class User;

struct score {
	string name;
	int val;
	bool operator<(const score& other) const {
		if (val != other.val)
			return val > other.val;
		return name < other.name;
	}
};

class Window : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int width, height;
	wxBitmap* logo;
	wxImage loadLogo(wxString path);
	wxImage image;
	wxBitmap *background, *about, *hsimage;
	wxFrame* parent;
	wxStatusBar *windowStatusBar;
	bool drawAbout = false;
	bool drawHighScore = false;
	wxTimer *timer;
	User *user;
	bool editStatus = false;
	clock_t cursor;
	vector<score> scores;

public:
	Window(wxFrame *parent, User* user);
	~Window();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnChar(wxKeyEvent &event);
};

