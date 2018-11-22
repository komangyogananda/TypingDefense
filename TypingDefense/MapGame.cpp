#include "MapGame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Window.h"
#include "Frame.h"

BEGIN_EVENT_TABLE(MapGame, wxWindow)
	EVT_BUTTON(1003, MapGame::OnButtonClick)
	EVT_PAINT(MapGame::OnPaint)
END_EVENT_TABLE()

MapGame::MapGame(wxFrame * parent) : wxWindow(parent, wxID_ANY)
{
	this->parent = parent;
	parent->GetSize(&width, &height);
	int w, h;
	this->GetSize(&w, &h);
	wxMessageOutputDebug().Printf("MAP GAME p %d %d\n", width, height);
	wxMessageOutputDebug().Printf("MAP GAME %d %d\n", w, h);
	this->SetSize(wxSize(width, height));
	backToMainMenu = new wxButton(this, 1003, wxT("Back To Main Menu"), wxPoint(width - 200, height - 200), wxDefaultSize);
	background = nullptr;
}

MapGame::~MapGame()
{
	delete background;
	delete backToMainMenu;
}

wxImage MapGame::loadLogo(wxString path) {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + path;
	wxImage image(fileLocation, wxBITMAP_TYPE_PNG);
	return image;
}

void MapGame::OnPaint(wxPaintEvent& event) {
	int w, h;
	parent->GetSize(&w, &h);
	wxImage image = loadLogo(wxT("\\map2.png"));
	wxSize a = image.GetSize();
	double aspectRatio = (double)a.GetHeight() / a.GetWidth();
	image.Rescale(w, h, wxIMAGE_QUALITY_NORMAL);
	background = new wxBitmap(image);
	wxPaintDC pdc(this);
	if (background != nullptr)
	{
		pdc.DrawBitmap(*background, wxPoint(0,0), true);
	}
}

void MapGame::OnButtonClick(wxCommandEvent & event)
{
	if (event.GetId() == 1003) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(1);
	}
}
