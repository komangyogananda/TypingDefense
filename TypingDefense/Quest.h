#pragma once
#include "wx/wx.h"
#include <string>

using namespace std;

class Quest :
	public wxWindow
{
private:
	string current;
	string target;
	string LCP;
	int coorX = 100, coorY = 100;

public:
	Quest();
	~Quest();
};

