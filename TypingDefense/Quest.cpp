#include "Quest.h"



void Quest::initWords()
{
	ifstream file("words.txt");
	string line;
	while (getline(file, line))
		randomTarget.push_back(line);
}

void Quest::randomizeTarget()
{
	srand(time(0));
	int id = rand() % randomTarget.size();
	setTarget(randomTarget[id]);
}

bool Quest::check()
{
	if (LCP == target) {
		return true;
	}
	return false;
}

void Quest::clearCurrent()
{
	current.clear();
}

void Quest::clearTarget()
{
	target.clear();
}

void Quest::clearLCP()
{
	LCP.clear();
}

void Quest::addCurrent(char c)
{
	current.push_back(c);
	setLCP();
}

void Quest::remCurrent()
{	
	if (!current.empty())
		current.pop_back();
	setLCP();
}

void Quest::setTarget(string s)
{
	target = s;
}

void Quest::setLCP()
{
	clearLCP();
	for (int i = 0; i < min(current.size(), target.size()); i++) {
		if (target[i] != current[i]) break;
		LCP.push_back(target[i]);
	}
}

string Quest::getCurrent()
{
	return current;
}

string Quest::getTarget()
{
	return target;
}

string Quest::getLCP()
{
	return LCP;
}

Quest::Quest()
{
	initWords();
}


Quest::~Quest()
{
}
