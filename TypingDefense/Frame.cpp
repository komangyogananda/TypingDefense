#include "Frame.h"
#include "User.h"

Frame::Frame(const wxString & title) : wxFrame(NULL, wxID_ANY, title)
{
	user = new User("Guest");
	this->ShowFullScreen(true);
	this->window = new Window(this, user);
	this->window->Show(true);

}

void Frame::setCurrentWindow(int a) {
	this->window->Destroy();
	if (a == 1) {
		this->window = new Window(this, user);
	}
	else {
		this->window = new MapGame(this, user);
	}
	this->window->Refresh();
}

Frame::~Frame()
{
	delete window;
	delete user;
}
