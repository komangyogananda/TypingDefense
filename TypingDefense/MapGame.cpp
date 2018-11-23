#include "MapGame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Window.h"
#include "Frame.h"
#include <string>

using namespace std;

BEGIN_EVENT_TABLE(MapGame, wxWindow)
	EVT_BUTTON(1003, MapGame::OnButtonClick)
	EVT_LEFT_DOWN(MapGame::OnClick)
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
	mapStatusBar = new wxStatusBar(this->parent, -1);
	mapStatusBar->SetStatusText(wxT("Test ini map game"));
	this->parent->SetStatusBar(mapStatusBar);
}

MapGame::~MapGame()
{
	delete background;
	delete backToMainMenu;
	//delete mapStatusBar;
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
	wxImage image = loadLogo(wxT("\\Map.png"));
	wxSize a = image.GetSize();
	double aspectRatio = (double)a.GetHeight() / a.GetWidth();
	image.Rescale(w, h, wxIMAGE_QUALITY_NORMAL);
	background = new wxBitmap(image);
	wxPaintDC pdc(this);
	if (background != nullptr)
	{
		pdc.DrawBitmap(*background, wxPoint(0,0), true);
	}
	image = loadLogo(wxT("\\snow.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	wxBitmap *skill = new wxBitmap(image);
	skillButton.clear();
	if (skill != nullptr) {
		pdc.DrawBitmap(*skill, wxPoint(3*w/4, 9*h/10), true);
	}
	koordinatBox skillNow;
	skillNow.x1 = 3 * w / 4;
	skillNow.x2 = 3 * w / 4 + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	image = loadLogo(wxT("\\meteor.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skill = new wxBitmap(image);
	int next = 3 * w / 4 + image.GetWidth() + 10;
	if (skill != nullptr) {
		pdc.DrawBitmap(*skill, wxPoint(next, 9 * h / 10), true);
	}
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();
	image = loadLogo(wxT("\\tembok.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skill = new wxBitmap(image);
	if (skill != nullptr) {
		pdc.DrawBitmap(*skill, wxPoint(next, 9 * h / 10), true);
	}
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
}

void MapGame::OnClick(wxMouseEvent & event)
{
	int x = event.GetX();
	int y = event.GetY();
	string status = "outside";
	for (int i = 0; i < skillButton.size(); i++) {
		koordinatBox now = skillButton[i];
		wxMessageOutputDebug().Printf("x1 = %d y1 = %d x2 = %d y2 = %d", now.x1, now.y1, now.x2, now.y2);
		if (now.x1 <= x && x <= now.x2) {
			if (now.y1 <= y && y <= now.y2) {
				status = "Skill" + to_string(i + 1);
			}
		}
	}
	mapStatusBar->SetStatusText(status);
}

void MapGame::OnButtonClick(wxCommandEvent & event)
{
	if (event.GetId() == 1003) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(1);
	}
}