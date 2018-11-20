#pragma once
#include "wx\wx.h"
#include "Window.h"
#include "MapGame.h"

class Frame : public wxFrame
{
private:
	wxWindow *window;
	wxWindow *map;
public:
	Frame(const wxString &title);
	void setCurrentWindow(int a);
	~Frame();
};

