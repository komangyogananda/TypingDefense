#include "Frame.h"

Frame::Frame(const wxString & title) : wxFrame(NULL, wxID_ANY, title)
{
	this->SetInitialSize(wxSize(1280, 720));
	this->window = new Window(this);
	this->window->Show(true);
	CreateStatusBar();
	SetStatusText("test");
}

void Frame::setCurrentWindow(int a) {
	this->window->Destroy();
	if (a == 1) {
		this->window = new Window(this);
	}
	else {
		this->window = new MapGame(this);
	}
	this->window->Refresh();
}

Frame::~Frame()
{
}
