#include "User.h"


User::User(string nama)
{
	this->nama = nama;
	this->money = 200;
	this->lifePoint = this->maxLifePoint = 500;
	this->score = 0;
}

int User::getMoney()
{
	return money;
}

void User::setMoney(int money)
{
	this->money = money;
}

string User::getNama()
{
	return nama;
}

void User::setNama(string nama)
{
	this->nama = nama;
}

void User::setLevel(int level)
{
	this->level = level;
}

int User::getLevel()
{
	return level;
}

int User::getScore()
{
	return score;
}

User::~User()
{
}
