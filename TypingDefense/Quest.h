#pragma once
#include "wx/wx.h"
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

class Quest :
	public wxWindow
{
private:
	string current;
	string target;
	string LCP;
	int coorX = 100, coorY = 100;
	vector<string> randomTarget;

public:
	void initWords();
	void randomizeTarget();
	bool check();
	void clearCurrent();
	void clearTarget();
	void clearLCP();
	void addCurrent(char c);
	void remCurrent();
	void setTarget(string s);
	void setLCP();
	string getCurrent();
	string getTarget();
	string getLCP();
	Quest();
	~Quest();
};

