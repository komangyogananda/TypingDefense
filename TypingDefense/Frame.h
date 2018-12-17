#pragma once
#include "wx\wx.h"
#include "Window.h"
#include "MapGame.h"

class User;

class Frame : public wxFrame
{
private:
	wxWindow *window;
	User *user;

public:
	Frame(const wxString &title);
	void setCurrentWindow(int a);
	~Frame();
};

