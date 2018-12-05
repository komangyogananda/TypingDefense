#include "User.h"


User::User(string nama)
{
	this->nama = nama;
	this->money = 100;
	this->maxMana = this->mana = 200;
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

User::~User()
{
}
