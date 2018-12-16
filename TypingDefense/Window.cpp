#include "Window.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "MapGame.h"
#include "Frame.h"
#include<iostream>
using namespace std;
BEGIN_EVENT_TABLE(Window, wxWindow)
	EVT_PAINT(Window::OnPaint)
	EVT_LEFT_DOWN(Window::OnClick)
	EVT_TIMER(1001, Window::OnTimer)
END_EVENT_TABLE()

Window::Window(wxFrame *parent) : wxWindow(parent, wxID_ANY)
{
	this->parent = parent;
	parent->GetSize(&width, &height);
	int w, h;
	this->SetSize(wxSize(width, height));
	logo = nullptr;
	this->SetBackgroundColour(wxColour(204, 172, 106));
	image = loadLogo("\\menu.png");
	image.Rescale(width, height);
	background = new wxBitmap(image);
	image = loadLogo("\\about.png");
	image.Rescale(width, height);
	about = new wxBitmap(image);
	image = loadLogo("\\highscore.png");
	image.Rescale(width, height);
	hsimage = new wxBitmap(image);
	timer = new wxTimer(this, 1001);
	timer->Start(10);
}

Window::~Window()
{
	delete logo;
	delete windowStatusBar;
	delete background;
	delete about;
	delete hsimage;
	delete timer;
}

wxImage Window::loadLogo(wxString path) {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + path;
	wxImage image(fileLocation, wxBITMAP_TYPE_PNG);
	return image;
}

void Window::OnPaint(wxPaintEvent& event) {
	int w, h;
	parent->GetSize(&w, &h);
	wxBufferedPaintDC pdc(this);
	pdc.DrawBitmap(*background, wxPoint(0, 0), true);
	if (drawAbout) {
		pdc.DrawBitmap(*about, wxPoint(0, 0), true);
	}
	if (drawHighScore) {
		pdc.DrawBitmap(*hsimage, wxPoint(0, 0), true);
	}
}

void Window::OnButtonClick(wxCommandEvent& event)
{
	if (event.GetId() == 1001) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(2);
	}
	else if (event.GetId() == 1002) {
		wxMessageBox(wxT("High Score"));
	}
}

void Window::OnClick(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	int w, h;
	this->parent->GetSize(&w, &h);
	wxMessageOutputDebug().Printf("x = %d, y = %d", x, y);
	int X1 = 760 * w / 1920;
	int playGameY1 = 556 * h / 1080;
	int X2 = 1160 * w / 1920;
	int playGameY2 = 640 * h / 1080;
	int aboutY1 = 807 * h / 1080;
	int aboutY2 = 890 * h / 1080;
	int hsY1 = 681 * h / 1080;
	int hsY2 = 766 * h / 1080;
	if (X1 <= x && x <= X2) {
		if (playGameY1 <= y && y <= playGameY2) {
			Frame *currFrame = (Frame*)parent;
			currFrame->setCurrentWindow(2);
		}
		else if (aboutY1 <= y && y <= aboutY2) {
			if (!drawAbout && !drawHighScore) {
				drawAbout = true;
			}
		}
		else if (hsY1 <= y && y <= hsY2) {
			if (!drawAbout && !drawHighScore) {
				drawHighScore = true;
			}
		}
	}
	int exitX1 = 1737 * w / 1920;
	int exitX2 = 1900 * w / 1920;
	int exitY1 = 976 * h / 1080;
	int exitY2 = 1061 * h / 1080;
	if (exitX1 <= x && x <= exitX2) {
		if (exitY1 <= y && y <= exitY2) {
			this->parent->Close(true);
		}
	}

	int closeAboutX1 = 1514 * w / 1920;
	int closeAboutX2 = 1542 * w / 1920;
	int closeAboutY1 = 261 * h / 1080;
	int closeAboutY2 = 310 * h / 1080;
	if (closeAboutX1 <= x && x <= closeAboutX2) {
		if (drawAbout) drawAbout = false;
	}

	int closeHighScoreX1 = 1330 * w / 1920;
	int closeHighScoreX2 = 1358 * w / 1920;
	int closeHighScoreY1 = 357 * h / 1080;
	int closeHighScoreY2 = 406 * h / 1080;
	if (closeHighScoreX1 <= x && x <= closeHighScoreX2) {
		if (drawHighScore) drawHighScore = false;
	}
}

void Window::OnTimer(wxTimerEvent & event)
{
	Refresh(0);
}
