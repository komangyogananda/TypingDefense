#pragma once
#include <string>
using namespace std;

class User
{
private:
	string nama;
	int money, mana, level, lifePoint, score;
	int maxMana, maxLifePoint;
	friend class MapGame;
public:
	User(string nama);
	~User();
};

