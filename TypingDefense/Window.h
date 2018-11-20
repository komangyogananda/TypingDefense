#pragma once
#include "wx/wx.h"

class Window : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int width, height;
	wxBitmap* logo;
	wxImage loadLogo();
	wxFrame* parent;
	wxImage image;
public:
	Window(wxFrame *parent);
	~Window();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
};

