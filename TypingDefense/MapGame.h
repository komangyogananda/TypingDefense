#pragma once
#include "wx/wx.h"
#include <vector>

struct koordinatBox {
	int x1, y1, x2, y2;
};

class MapGame : public wxWindow
{
private:
	DECLARE_EVENT_TABLE()
	int width, height;
	wxFrame* parent;
	wxBitmap* background;
	wxImage image;
	wxButton *backToMainMenu;
	wxStatusBar *mapStatusBar;
	wxImage loadLogo(wxString path);
	std::vector<koordinatBox> skillButton;
public:
	MapGame(wxFrame *parent);
	~MapGame();
	void OnButtonClick(wxCommandEvent &event);
	void OnPaint(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);
};

