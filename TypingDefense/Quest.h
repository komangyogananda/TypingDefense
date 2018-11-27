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
	string errorMessage;
	string successMessage;
	int coorX = 100, coorY = 100;
	vector<string> randomTarget;
	vector<string> randomError;
	vector<string> randomSuccess;
	int status = 0;

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
	void setStatus(int s);
	int getStatus();
	void randomizeErrorMessage();
	void randomizeSuccessMessage();
	string getErrorMessage();
	string getSuccessMessage();
	string getCurrent();
	string getTarget();
	string getLCP();
	Quest();
	~Quest();
};

