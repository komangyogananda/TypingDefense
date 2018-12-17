#include "Window.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "MapGame.h"
#include "Frame.h"
#include<iostream>
#include "User.h"

using namespace std;
BEGIN_EVENT_TABLE(Window, wxWindow)
	EVT_PAINT(Window::OnPaint)
	EVT_LEFT_DOWN(Window::OnClick)
	EVT_TIMER(1001, Window::OnTimer)
	EVT_CHAR(Window::OnChar)
END_EVENT_TABLE()

Window::Window(wxFrame *parent, User* user) : wxWindow(parent, wxID_ANY)
{
	this->SetFocus();
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
	this->user = user;
	cursor = clock();
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
	int textX = 780 * w / 1920;
	int textY = 930 * h / 1080;
	wxFont fontNama(20, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	pdc.SetFont(fontNama);
	string nama = user->getNama();
	if (editStatus) {
		if (fmod(double(clock() - cursor) / CLOCKS_PER_SEC, 2) <= 1.0) {
			nama.push_back('|');
		}
	}
	pdc.DrawText(nama, wxPoint(textX, textY));
	wxMessageOutputDebug().Printf("%d", editStatus);
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
	
	if (!drawAbout && !drawHighScore) {
		if (X1 <= x && x <= X2) {
			if (playGameY1 <= y && y <= playGameY2) {
				Frame *currFrame = (Frame*)parent;
				currFrame->setCurrentWindow(2);
			}
			else if (aboutY1 <= y && y <= aboutY2) {
				if (!drawAbout && !drawHighScore) {
					drawAbout = true;
					editStatus = false;
				}
			}
			else if (hsY1 <= y && y <= hsY2) {
				if (!drawAbout && !drawHighScore) {
					drawHighScore = true;
					editStatus = false;
				}
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
		if (closeAboutY1 <= y && y <= closeAboutY2) {
			if (drawAbout) drawAbout = false;
		}
	}

	int closeHighScoreX1 = 1330 * w / 1920;
	int closeHighScoreX2 = 1358 * w / 1920;
	int closeHighScoreY1 = 357 * h / 1080;
	int closeHighScoreY2 = 406 * h / 1080;
	if (closeHighScoreX1 <= x && x <= closeHighScoreX2) {
		if (closeHighScoreY1 <= y && y <= closeHighScoreY2) {
			if (drawHighScore) drawHighScore = false;
		}
	}

	int editX1 = 1178 * w / 1920;
	int editY1 = 917 * h / 1080;
	int editX2 = 1305 * w / 1920;
	int editY2 = 977 * h / 1080;
	if (!drawAbout && !drawHighScore) {
		if (editX1 <= x && x <= editX2) {
			if (editY1 <= y && y <= editY2) {
				if (editStatus) editStatus = false;
				else editStatus = true;
			}
		}
	}
}

void Window::OnTimer(wxTimerEvent & event)
{
	Refresh(0);
}

void Window::OnChar(wxKeyEvent & event)
{
	string temp = user->getNama();
	if (editStatus) {
		if (event.GetKeyCode() == WXK_BACK) {
			if (!temp.empty()) {
				temp.pop_back();
			}
		}
		else if (event.GetKeyCode() >= -1 && event.GetKeyCode() <= 255 && isprint(event.GetKeyCode()) && (temp.size() < 20)) {
			char x = event.GetKeyCode();
			temp.push_back(x);
		}
	}
	user->setNama(temp);
}
