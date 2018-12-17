#include "Monster.h"
#include "MapGame.h"
#include "Tower.h"

BEGIN_EVENT_TABLE(Monster, wxEvtHandler)
	EVT_TIMER(2000, Monster::OnTimer)
	EVT_TIMER(2001, Monster::AnimationTimer)
END_EVENT_TABLE()

Monster::~Monster()
{
	delete animationTimer;
	delete timer;
}

void Monster::moveX(double point)
{
	this->x += point;
}

void Monster::moveY(double point)
{
	this->y += point;
}

void Monster::followTarget()
{
	double sX = targetX - this->x;
	double sY = targetY - this->y;
	double sMiring = sqrt(pow(sX, 2) + pow(sY, 2));
	double ratio = (double)this->v / sMiring;
	double tempVx = ratio * sX;
	double tempVy = ratio * sY;
	vx = round(tempVx);
	vy = round(tempVy);
	vx = vx * (100-slow) / 100;
	vy = vy * (100-slow) / 100;
}

void Monster::OnTimer(wxTimerEvent & event)
{
	if (tauntStatus) {
		setTarget(-1, -1);
		tauntStatus = false;
	}
	if (stunStatus) {
		setSlow(0);
		stunStatus = false;
	}
	timer->Stop();
}

void Monster::AnimationTimer(wxTimerEvent & event)
{
	if (!stunStatus){
		idx++;
	}
}

Monster::Monster(MapGame *mapGame, int maxHealthPoint, int attackPoint, int x, int y, int targetX, int targetY, int level)
{
	map = mapGame;
	this->maxHealthPoint = maxHealthPoint;
	this->healthPoint = maxHealthPoint;
	this->attackPoint = attackPoint;
	this->x = x + 35;
	this->y = y + 35;
	this->level = level;
	this->targetX = targetX;
	this->targetY = targetY;
	this->slow = 0;
	timer = new wxTimer(this, 2000);
	animationTimer = new wxTimer(this, 2001);
	animationTimer->Start(20);
}

void Monster::jalan()
{
	followTarget();
	//wxMessageOutputDebug().Printf("%d %d", vx, vy);
	moveX(vx);
	moveY(vy);
}

int Monster::draw(wxBufferedPaintDC &pdc, vector<wxBitmap*> *animation) {
	if (mati()) return 0;
	if (attack()) return attackPoint;

	///*pdc.SetBrush(wxBrush(wxColour(255,255,255)));
	//pdc.DrawCircle(wxPoint(x, y), r);*/
	//idx = idx % 12;
	//pdc.DrawBitmap(*(*animation)[idx++], wxPoint(x - 35, y - 35), false);
	//pdc.SetBrush(wxBrush(wxTransparentColour., wxBRUSHSTYLE_TRANSPARENT));
	//pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	////pdc.DrawRectangle(x - 35, y - 35, 70, 70);
	//pdc.DrawRectangle(x - 35, y + 35, 70, 5);
	//pdc.SetBrush(wxBrush(wxColour(255*(maxHealthPoint - healthPoint)/maxHealthPoint, 255*healthPoint/maxHealthPoint, 0), wxBRUSHSTYLE_SOLID));
	//pdc.DrawRectangle(x-35, y + 35, healthPoint*70/maxHealthPoint, 5);

	wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);

	idx = idx % 12;

	if (gc) {
		gc->DrawBitmap(*(*animation)[idx], x - 35, y - 35, 70, 70);
		gc->SetPen(*wxWHITE_PEN);
		gc->SetBrush(*wxWHITE_BRUSH);
		gc->DrawRectangle(x - 35, y + 35, 70, 5);
		gc->SetBrush(wxBrush(wxColour(255 * (maxHealthPoint - healthPoint) / maxHealthPoint, 255 * healthPoint / maxHealthPoint, 0), wxBRUSHSTYLE_SOLID));
		gc->DrawRectangle(x - 35, y + 35, healthPoint * 70 / maxHealthPoint, 5);
		delete gc;
	}
	return -1;
}

bool Monster::mati()
{
	if (healthPoint <= 0) {
		return true;
	}
	return false;
}

double Monster::getX()
{
	return x;
}

double Monster::getY()
{
	return y;
}

int Monster::getRadius()
{
	return r;
}

void Monster::getDamage(int damage)
{
	this->healthPoint -= damage;
	if (this->healthPoint < 0) this->healthPoint = 0;
}

void Monster::setSlow(int slow)
{
	this->slow = slow;
}

int Monster::getSlow()
{
	return this->slow;
}

void Monster::setTarget(double x, double y)
{
	this->targetX = x;
	this->targetY = y;
	if (x == -1 && y == -1) {
		int w, h;
		map->GetSize(&w, &h);
		this->targetX = w;
		this->targetY = h / 2;
	}
}

void Monster::tauntedBy(Tower* taunt)
{
	tauntStatus = true;
	tauntTower.push_back(taunt);
	timer->Start(2000);
}

void Monster::stunnedBy(Tower * stun)
{
	stunStatus = true;
	stunTower.push_back(stun);
	timer->Start(3000);
}

bool Monster::checkTaunt(Tower * taunt)
{
	for (auto it : tauntTower) {
		if (it == taunt) return false;
	}
	return true;
}

bool Monster::checkStun(Tower * stun)
{
	for (auto it : stunTower) {
		if (it == stun) return false;
	}
	return true;
}

bool Monster::getTauntStatus()
{
	return tauntStatus;
}

bool Monster::getStunStatus()
{
	return stunStatus;
}

bool Monster::attack() {
	int x;
	map->GetSize(&x, NULL);
	if (this->x >= x) return true;
	return false;
}
