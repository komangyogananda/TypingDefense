#pragma once
#include "wx/wx.h"

class User;

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

public:
	Window(wxFrame *parent, User* user);
	~Window();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
	void OnTimer(wxTimerEvent &event);
	void OnChar(wxKeyEvent &event);
};

