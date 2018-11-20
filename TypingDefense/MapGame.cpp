#include "MapGame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Window.h"
#include "Frame.h"

BEGIN_EVENT_TABLE(MapGame, wxWindow)
	EVT_BUTTON(1003, MapGame::OnButtonClick)
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
	wxButton *backToMainMenu = new wxButton(this, 1003, wxT("Back To Main Menu"), wxPoint(width - 200, height - 200), wxDefaultSize);
	wxBitmap* background = nullptr;
	this->SetBackgroundColour(wxColour(0, 255, 0));
}

MapGame::~MapGame()
{
}

void MapGame::OnButtonClick(wxCommandEvent & event)
{
	if (event.GetId() == 1003) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(1);
	}
}
