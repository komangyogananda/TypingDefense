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
public:
	MapGame(wxFrame *parent);
	~MapGame();
	void OnButtonClick(wxCommandEvent &event);
};

