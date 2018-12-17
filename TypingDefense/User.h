#pragma once
#include <string>
using namespace std;

class User
{
private:
	string nama;
	int money, level, lifePoint, score;
	int maxLifePoint;
	friend class MapGame;
public:
	User(string nama);
	int getMoney();
	void setMoney(int money);
	string getNama();
	void setNama(string nama);
	void setLevel(int level);
	int getLevel();
	int getScore();
	~User();
};

