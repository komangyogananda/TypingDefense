#pragma once
#include "wx/wx.h"

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int width, height;
	wxFrame* parent;
	wxBitmap* background;
	wxImage image;
	wxButton *backToMainMenu;
	wxImage loadLogo(wxString path);
public:
	MapGame(wxFrame *parent);
	~MapGame();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
};

