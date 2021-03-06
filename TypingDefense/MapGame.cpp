#include "MapGame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Window.h"
#include "Frame.h"
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>

BEGIN_EVENT_TABLE(MapGame, wxWindow)
	EVT_KEY_DOWN(MapGame::OnKeyDown)
	EVT_CHAR(MapGame::OnChar)
	EVT_TIMER(2000, MapGame::OnTimer)
	EVT_TIMER(2001, MapGame::QuestGiver)
	EVT_TIMER(2002, MapGame::SpawnMonster)
	EVT_TIMER(2003, MapGame::NoCoin)
	EVT_LEFT_DOWN(MapGame::OnClick)
	EVT_PAINT(MapGame::OnPaint)
END_EVENT_TABLE()

MapGame::MapGame(wxFrame * parent, User* user) : wxWindow(parent, wxID_ANY)
{
	srand(time(0));

	image = loadLogo(wxT("\\towerBasic.png"));
	towerImage.push_back(new wxBitmap(image));

	image = loadLogo(wxT("\\towerSlow.png"));
	towerImage.push_back(new wxBitmap(image));

	image = loadLogo(wxT("\\towerTaunt.png"));
	towerImage.push_back(new wxBitmap(image));

	image = loadLogo(wxT("\\towerStun.png"));
	towerImage.push_back(new wxBitmap(image));

	this->SetFocus();
	
	quest = new Quest();
	this->quest->setStatus(0);
	
	this->user = user;
	user->lifePoint = 500;

	this->parent = parent;
	this->parent->GetSize(&w, &h);
	this->SetSize(wxSize(w, h));

	timer = new wxTimer(this, 2000);
	timer->Start(10);


	nocointimer = new wxTimer(this, 2003);

	spawnTimer = new wxTimer(this, 2002);

	questTimer = new wxTimer(this, 2001);
	questTimer->Start(3000);
	this->now = clock();
	this->wallCD = this->snowCD = this->meteorCD = clock() - (30 * CLOCKS_PER_SEC);
	this->cooldownTimer = clock();

	background = nullptr;
	
	/*Monster *test = new Monster(this, 100, 35, 0, wxGetDisplaySize().GetHeight() / 2, w, h/2, 1);
	allMonster.push_back(test);*/

	image = loadLogo(wxT("\\Map.png"));
	wxSize a = image.GetSize();
	double aspectRatio = (double)a.GetHeight() / a.GetWidth();
	image.Rescale(w, h, wxIMAGE_QUALITY_NORMAL);
	background = new wxBitmap(image);

	/*image = loadLogo(wxT("\\coin.png"));
	image.Rescale(100, image.GetHeight() * 100 / image.GetWidth());
	coin = new wxBitmap(image);*/

	this->activeButton = nullptr;
	this->meteorButton = new MeteorButton(this, &allTower, &allMonster, &allBullet, &allSkill);
	this->snowButton = new SnowButton(this, &allTower, &allMonster, &allBullet, &allSkill);
	this->wallButton = new WallButton(this, &allTower, &allMonster, &allBullet, &allSkill);
	this->basicButton = new BasicButton(this, &allTower, &allMonster, &allBullet, &allSkill, &towerImage);
	this->slowButton = new SlowButton(this, &allTower, &allMonster, &allBullet, &allSkill, &towerImage);
	this->stunButton = new StunButton(this, &allTower, &allMonster, &allBullet, &allSkill, &towerImage);
	this->tauntButton = new TauntButton(this, &allTower, &allMonster, &allBullet, &allSkill, &towerImage);

	image = loadLogo(wxT("\\quest.png"));
	image.Rescale(w, h);
	questBackground = new wxBitmap(image);
	
	image = loadLogo(wxT("\\clock.png"));
	image.Rescale(25, 25);
	questClock = new wxBitmap(image);

	image = loadLogo(wxT("\\nocoin.png"));
	nocoin = new wxBitmap(image);

	image = loadLogo(wxT("\\questImage1.png"));
	image.Rescale(100, 100);
	questImage1 = new wxBitmap(image);

	image = loadLogo(wxT("\\questImage2.png"));
	image.Rescale(100, 100);
	questImage2 = new wxBitmap(image);

	image = loadLogo(wxT("\\questImage3.png"));
	image.Rescale(120, 120);
	questImage3 = new wxBitmap(image);

	image = loadLogo(wxT("\\pause.png"));
	pauseBar = new wxBitmap(image);

	image = loadLogo(wxT("\\stage.png"));
	levelUpImage = new wxBitmap(image);

	image = loadLogo(wxT("\\wave.png"));
	waveIncoming = new wxBitmap(image);

	for (int i = 1; i < 13; i++) {
		image = loadLogo(wxT("\\monster\\monster" + to_string(i) + ".png"));
		image.Rescale(70, 70);
		animationMonster.push_back(new wxBitmap(image));
	}

	for (int i = 0; i < 10; i++) {
		image = loadLogo(wxT("\\coin\\coin" + to_string(i) + ".png"));
		image.Rescale(image.GetWidth() / 8, image.GetHeight() / 8);
		coin.push_back(new wxBitmap(image));
	}

	for (int i = 1; i < 9; i++) {
		image = loadLogo(wxT("\\meteor\\meteor" + to_string(i) + ".png"));
		meteorPng.push_back(new wxBitmap(image));
	}

	image = loadLogo(wxT("\\snow\\snow.png"));
	snowPng.push_back(new wxBitmap(image));

	image = loadLogo(wxT("\\wall\\wall.png"));
	image.Rescale(50, 100);
	wallPng.push_back(new wxBitmap(image));


	image = loadLogo(wxT("\\snow.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	wxBitmap *skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	koordinatBox skillNow;
	skillNow.x1 = 2 * w / 3;
	skillNow.x2 = 2 * w / 3 + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	
	image = loadLogo(wxT("\\meteor.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	int next = 2 * w / 3 + image.GetWidth() + 10;
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	image = loadLogo(wxT("\\tembok.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	image = loadLogo(wxT("\\basictower.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	image = loadLogo(wxT("\\slowtower.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	image = loadLogo(wxT("\\taunttower.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	image = loadLogo(wxT("\\stuntower.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	skillNow.x1 = next;
	skillNow.x2 = next + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	next += 10 + image.GetWidth();

	this->placeholder = nullptr;

	level = new Level(1);
	spawnTimer->Start(1000 * level->getTimePerMonster());

	/*tower = new StunTower(1300, 450, allMonster, &towerImage);
	allTower.push_back(tower);*/
}

void MapGame::changeWindow()
{
	Frame * currFrame = (Frame*)parent;
	currFrame->setCurrentWindow(1);
	return;
}

int MapGame::randNum(int low, int high)
{
	int ans = 0;
	int md = high - low + 1;
	ans = (rand() % md) + low;
	return ans;
}

MapGame::~MapGame()
{
	for (auto it : allSkill) {
		delete it;
	}
	for (auto it : allBullet) {
		delete it;
	}
	for (auto it : allTower) {
		delete it;
	}
	for (auto it : skill) {
		delete it;
	}
	for (auto it : animationMonster) {
		delete it;
	}
	for (auto it : coin) {
		delete it;
	}
	for (auto it : towerImage) {
		delete it;
	}
	for (auto it : meteorPng) {
		delete it;
	}
	for (auto it : snowPng) {
		delete it;
	}
	for (auto it : wallPng) {
		delete it;
	}
	for (auto it : allMonster) {
		delete it;
	}
	delete meteorButton;
	delete snowButton;
	delete wallButton;
	delete curSkill;
	delete nocoin;
	delete nocointimer;
	delete questImage1;
	delete questImage2;
	delete questImage3;
	delete background;
	delete timer;
	delete questTimer;
	delete quest;
	delete questClock;
	delete spawnTimer;
	delete basicButton;
	delete slowButton;
	delete stunButton;
	delete tauntButton;
	delete level;
	delete levelUpImage;
	delete waveIncoming;
	delete pauseBar;
	delete questBackground;
}

wxImage MapGame::loadLogo(wxString path) {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + path;
	wxImage image(fileLocation, wxBITMAP_TYPE_PNG);
	return image;
}

void MapGame::OnPaint(wxPaintEvent& event) {
	wxBufferedPaintDC pdc(this);

	pdc.DrawBitmap(*background, wxPoint(0, 0), true);
	coinIdx = coinIdx % 30;
	pdc.DrawBitmap(*coin[coinIdx / 3], wxPoint(9 * wxGetDisplaySize().GetWidth() / 10, 10));
	coinIdx++;
	coinSize = wxSize(9 * wxGetDisplaySize().GetWidth() / 10 + coin[0]->GetWidth() + 10, 10);
	//pdc.DrawBitmap(*coin, wxPoint(9 * wxGetDisplaySize().GetWidth() / 10, 2));
	//coinSize = wxSize(9 * wxGetDisplaySize().GetWidth() / 10 + coin->GetWidth() + 10, 2);

	if (nocoinstatus) {
		pdc.DrawBitmap(*nocoin, wxPoint(9 * wxGetDisplaySize().GetWidth() / 10 - nocoin->GetSize().GetWidth() - 10, 10));
	}

	drawHealthBar(pdc);
	MeteorButton* tmp = dynamic_cast<MeteorButton*>(activeButton);
	if (tmp == nullptr) {
		drawPlaceholderTower(pdc);
	}

	for (auto it : allTower) {
		it->draw(pdc);
	}

	for (int i = 0; i < skillButton.size(); i++) {
		pdc.DrawBitmap(*skill[i], wxPoint(skillButton[i].x1, skillButton[i].y1), true);
	}
	drawCooldown(pdc);

	for (auto it = allBullet.begin(); it != allBullet.end(); it++) {
		int kondisi = (*it)->checkCollision();
		(*it)->draw(pdc);
		if (kondisi) {
			(*it)->giveDamage();
			delete *it;
			it = allBullet.erase(it);
			if (it == allBullet.end()) break;
		}
		else if ((*it)->getTargetMonster() == nullptr) {
			delete *it;
			it = allBullet.erase(it);
			if (it == allBullet.end()) break;
		}
		else if ((*it)->getTargetMonster()->mati()) {
			delete *it;
			it = allBullet.erase(it);
			if (it == allBullet.end()) break;
		}
	}

	for (auto it = allSkill.begin(); it != allSkill.end(); it++) {
		Meteor* a = dynamic_cast<Meteor*>(*it);
		Snow* b = dynamic_cast<Snow*>(*it);
		Wall* c = dynamic_cast<Wall*>(*it);
		if (a != nullptr) {
			if ((*it)->getIdx() >= 8) {
				delete *it;
				it = allSkill.erase(it);
				if (it == allSkill.end()) break;

			}
			else {
				(*it)->active(pdc, &meteorPng);
			}
		}
		else if (b != nullptr) {
			if ((*it)->getIdx() >= 60) {
				delete *it;
				it = allSkill.erase(it);
				if (it == allSkill.end()) break;

			}
			else {
				(*it)->active(pdc, &snowPng);
			}
		}
		else if (c != nullptr) {
			if ((*it)->getIdx() >= 30) {
				delete *it;
				it = allSkill.erase(it);
				if (it == allSkill.end()) break;

			}
			else {
				(*it)->active(pdc, &wallPng);
			}
		}
	}

	for (auto it = allMonster.begin(); it != allMonster.end(); it++) {
		int kondisi = (*it)->draw(pdc, &animationMonster);
		if (kondisi != -1) {
			if (kondisi != 0) {
				minusHealth += (*it)->attackPoint;
				if (user->lifePoint <= 0) {
					user->lifePoint = 0;
					//changeWindow();
				}
			}
			else {
				user->money += 15;
				user->score += 30;
			}
			delete *it;
			level->setDiedMonster(level->getDiedMonster() + 1);
			it = allMonster.erase(it);
			if (it == allMonster.end()) break;
		}
	}

	if (!this->quest->getTarget().empty() && (this->quest)->check()) {
		(this->quest)->setStatus(1);
		user->money += (this->quest->getTarget()).size();
		user->score += (this->quest->getTarget()).size() * 2;
		(this->quest)->clearCurrent();
		(this->quest)->clearTarget();
		(this->quest)->clearLCP();
		questTimer->Start((rand() % 5 + 2) * 1000);
		this->statusTimer = clock();
		this->quest->randomizeSuccessMessage();
	}

	if (!this->quest->getTarget().empty()) {
		wxFont questFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		pdc.SetFont(questFont);
		
		auto tnow = (double)(clock() - this->now) / CLOCKS_PER_SEC;
		tnow *= 1000;
		auto sec = (this->questInterval - tnow) / 1000;

		if (sec <= 0) {
			(this->quest)->setStatus(2);
			this->quest->clearCurrent();
			this->quest->clearTarget();
			this->quest->clearLCP();
			questTimer->Start((rand() % 5 + 2) * 1000);
			this->statusTimer = clock();
			this->quest->randomizeErrorMessage();
		}

		string pointer = (fmod(sec, 1) > 0.5 ? "|" : " ");
		string stSec = to_string(sec);
		
		for (int i = 0; i < 3; i++) stSec.pop_back();
		
		pdc.SetPen(*wxWHITE_PEN);
		pdc.SetBrush(wxColor(RGB(81, 178, 128)));
		//pdc.DrawRectangle(wxPoint(75, wxGetDisplaySize().GetHeight() - 275), wxSize(13 * ((this->quest)->getTarget()).size()-20, 220));
		pdc.DrawBitmap(*questBackground, wxPoint(0, 0), true);
		pdc.DrawBitmap(*questClock, wxPoint(100 , wxGetDisplaySize().GetHeight() - 250));
		
		pdc.SetTextForeground(RGB(255, 255, 255));
		pdc.DrawText((this->quest)->getCurrent() + pointer, wxPoint(100, wxGetDisplaySize().GetHeight() - 150));
		pdc.SetTextForeground(RGB(128, 128, 128));
		pdc.DrawText((this->quest)->getTarget(), wxPoint(100, wxGetDisplaySize().GetHeight() - 180));
		pdc.SetTextForeground(RGB(255, 255, 0));
		pdc.DrawText(to_string((this->quest)->getTarget().size()) + " Coins", wxPoint(100, wxGetDisplaySize().GetHeight() - 215));
		if (sec > 50.0 / 100.0 * (double)this->questInterval / 1000.0)
			pdc.SetTextForeground(RGB(255.0 * 2.0 * (1.0 - (sec * 1000.0 / (double)this->questInterval)), 255, 0));
		else if (sec > 25.0 / 100.0 * (double)this->questInterval / 1000.0)
			pdc.SetTextForeground(RGB(255, 255 * (1.0 - 4.0 * (0.5 - (sec * 1000.0 / (double)this->questInterval))), 0));
		else pdc.SetTextForeground(RGB(255, 0, 0));

		pdc.DrawText(stSec + " s" , wxPoint(135, wxGetDisplaySize().GetHeight() - 247));
		pdc.SetTextForeground(RGB(0, 255, 0));
		pdc.DrawText((this->quest)->getLCP(), wxPoint(100, wxGetDisplaySize().GetHeight() - 180));
		pdc.SetTextForeground(RGB(0, 0, 0));

		if (((this->quest)->getCurrent()).size() == ((this->quest)->getTarget()).size()) {
			pdc.SetTextForeground(RGB(255, 0, 0));
			pdc.DrawText("MAX LIMIT REACHED!!" , wxPoint(150, wxGetDisplaySize().GetHeight() - 100));
		}
	}
	
	double statusNow = (double)(clock() - this->statusTimer) / CLOCKS_PER_SEC;
	
	if (this->quest->getStatus() == 0) {
		pdc.DrawBitmap(*questImage1, wxPoint(50, wxGetDisplaySize().GetHeight() - 120));
	}
	else if (this->quest->getStatus() == 1) {
		wxFont questFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		pdc.SetFont(questFont);
		pdc.SetPen(*wxWHITE_PEN);
		pdc.SetBrush(wxColor(RGB(0, 255, 0)));
		pdc.DrawBitmap(*questImage2, wxPoint(50, wxGetDisplaySize().GetHeight() - 120));
		if (statusNow < 4) {
			pdc.DrawRoundedRectangle(wxPoint(75, wxGetDisplaySize().GetHeight() - 220),
				wxSize(20 * ((this->quest)->getSuccessMessage()).size(), 70), 10);
			pdc.SetTextForeground(wxColor(*wxWHITE));
			pdc.DrawText((this->quest)->getSuccessMessage(), wxPoint(100, wxGetDisplaySize().GetHeight() - 200));
		}
		
	}
	else {
		wxFont questFont(13, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		pdc.SetFont(questFont);
		pdc.SetPen(*wxWHITE_PEN);
		pdc.SetBrush(wxColor(RGB(255, 0, 0)));
		pdc.DrawBitmap(*questImage3, wxPoint(50, wxGetDisplaySize().GetHeight() - 150));
		if (statusNow < 4) {
			pdc.DrawRoundedRectangle(wxPoint(75, wxGetDisplaySize().GetHeight() - 220),
				wxSize(20 * ((this->quest)->getErrorMessage()).size(), 70), 10);
			pdc.SetTextForeground(wxColor(*wxWHITE));
			pdc.DrawText((this->quest)->getErrorMessage(), wxPoint(100, wxGetDisplaySize().GetHeight() - 200));
		}
	}

	if (drawWaveImage) {
		pdc.DrawBitmap(*waveIncoming, wxPoint(0, 0), true);
	}

	if (drawLevelUpImage) {
		pdc.DrawBitmap(*levelUpImage, wxPoint(0, 0), true);
	}

	if (pause) {
		pdc.DrawBitmap(*pauseBar, wxPoint(0, 0), true);
		timerInterval = timer->GetInterval();
		timer->Stop();
	}

}

void MapGame::OnClick(wxMouseEvent & event)
{
	bool yes = false;
	int x = event.GetX();
	int y = event.GetY();

	//wxMessageOutputDebug().Printf("x = %d, y = %d", x, y);

	for (int i = 0; i < skillButton.size(); i++) {
		koordinatBox now = skillButton[i];
		if (now.x1 <= x && x <= now.x2) {
			if (now.y1 <= y && y <= now.y2) {
				yes = true;
				if (i == 0) {
					if ((double)(clock() - snowCD) / CLOCKS_PER_SEC < 30) {
						return;
					}
					activeButton = snowButton;
					return;
				}
				if (i == 1) {
					if ((double)(clock() - meteorCD) / CLOCKS_PER_SEC < 30) {
						return;
					}
					activeButton = meteorButton;
				}
				if (i == 2) {
					if ((double)(clock() - wallCD) / CLOCKS_PER_SEC < 30) {
						return;
					}
					activeButton = wallButton;
					return;
				}
				if (user->money >= 100 && i > 2) {
					if (i == 3) {
						activeButton = basicButton;
						return;
					}
					else if (i == 4) {
						activeButton = slowButton;
						return;
					}
					else if (i == 5) {
						activeButton = tauntButton;
						return;
					}
					else if (i == 6) {
						activeButton = stunButton;
						return;
					}
				}
				else if (i > 2){
					nocoinstatus = true;
					nocointimer->Start(2000);
				}
			}
		}
	}

	if (activeButton != nullptr) {
		SnowButton* a = dynamic_cast<SnowButton*>(activeButton);
		MeteorButton* b = dynamic_cast<MeteorButton*>(activeButton);
		WallButton* c = dynamic_cast<WallButton*>(activeButton);
		if (a != nullptr) {
			snowCD = clock();
		}
		else if (b != nullptr) {
			meteorCD = clock();
		}
		else if (c != nullptr) {
			wallCD = clock();
		}
		activeButton->execute();
		activeButton = nullptr;
	}


	int menuX1 = 761 * w / 1920;
	int pauseY1 = 425 * h / 1080;
	int menuX2 = 1163 * w / 1920;
	int pauseY2 = 504 * h / 1080;

	int mainMenuY1 = 570 * h / 1080;
	int mainMenuY2 = 658 * h / 1080;

	if (pause) {
		if (menuX1 <= x && x <= menuX2) {
			if (pauseY1 <= y && y <= pauseY2) {
				resumeGame();
			}
			else if (mainMenuY1 <= y && y <= mainMenuY2) {
				changeWindow();
			}
			return;
		}
	}

}

void MapGame::OnTimer(wxTimerEvent &event) {
	if (level->getLaunchedMonster() == level->getTotalMonster() / 2 && !drawWaveImage) {
		spawnTimer->Stop();
	}
	if (level->getDiedMonster() == level->getTotalMonster() / 2 && !drawWaveImage && level->getLaunchedMonster() == level->getTotalMonster() / 2) {
		drawWaveImage = true;
		spawnTimer->Start(5000);
	}
	if (level->getLaunchedMonster() == level->getTotalMonster()) {
		spawnTimer->Stop();
	}
	if (level->getDiedMonster() == level->getTotalMonster()) {
		this->LevelUp();
		spawnTimer->Start(10000);
		return;
	}
	if (user->lifePoint == 0) {
		fstream in;
		in.open("scores.txt", fstream::app);
		in << user->getNama() << " " << user->getScore() << "\n";
		in.close();
		changeWindow();
		return;
	}
	for (auto it : allMonster) {
		it->jalan();
	}
	Refresh(0);
}

void MapGame::OnKeyDown(wxKeyEvent & event)
{
	if (event.GetKeyCode() == WXK_BACK)
		(this->quest)->remCurrent();
	else if (event.GetKeyCode() == 27) {
		pauseGame();
	}
	else event.Skip();
}

void MapGame::OnChar(wxKeyEvent & event)
{
	if (event.GetKeyCode() >= -1 && event.GetKeyCode() <= 255 && isprint(event.GetKeyCode()) && 
		((this->quest)->getCurrent()).size() < ((this->quest)->getTarget()).size())
		(this->quest)->addCurrent(event.GetKeyCode());
	else event.Skip();
}

void MapGame::QuestGiver(wxTimerEvent & event)
{
	this->quest->clearCurrent();
	this->quest->clearTarget();
	this->quest->clearLCP();
	this->quest->randomizeTarget();
	this->now = clock();
	this->quest->setStatus(0);
	this->questInterval = ((double)(this->quest->getTarget()).size()) / 5 * 1000;
	questTimer->Stop();
}

void MapGame::NoCoin(wxTimerEvent & event)
{
	nocoinstatus = false;
	nocointimer->Stop();
}

void MapGame::SpawnMonster(wxTimerEvent & event)
{
	//wxMessageOutputDebug().Printf("%d", level->getDiedMonster());	
	Monster *spawn;
	if (drawLevelUpImage) drawLevelUpImage = false;
	if (drawWaveImage) {
		drawWaveImage = false;
		spawnTimer->Start(100);
	}
	int location = randNum(1, 3);
	int targetY = randNum(0.25*h, 0.68*h);
	if (location == 1) {
		int y = randNum(0.32*h, 0.5*h);
		spawn = new Monster(this, 100, 35, 0, y, w, targetY, 1);
	}
	else if (location == 2) {
		int x = randNum(0.5*w, 0.62*w);
		spawn = new Monster(this, 100, 35, x, 0, w, targetY, 1);
	}
	else if (location == 3) {
		int x = randNum(0.5*w, 0.62*w);
		spawn = new Monster(this, 100, 35, x, h, w, targetY, 1);
	}
	allMonster.push_back(spawn);
	level->setLaunchedMonster(level->getLaunchedMonster() + 1);
}

void MapGame::animationMinusHealthBar()
{
	if (minusHealth > 0) {
		minusHealth -= 1;
		user->lifePoint -= 1;
		if (user->lifePoint <= 0) user->lifePoint = 0;
	}
}

void MapGame::LevelUp()
{
	int currlevel = level->getLevel();
	delete level;
	level = new Level(currlevel + 1);
	drawLevelUpImage = true;
}

void MapGame::pauseGame()
{
	/*timerInterval = timer->GetInterval();
	timer->Stop();*/
	questTimerInterval = questTimer->GetInterval();
	questTimer->Stop();
	spawnTimerInterval = spawnTimer->GetInterval();
	spawnTimer->Stop();
	nocointimerInterval = nocointimer->GetInterval();
	nocointimer->Stop();
	pause = true;
}

void MapGame::resumeGame()
{
	timer->Start(timerInterval);
	timerInterval = -1;
	questTimer->Start(questTimerInterval);
	questTimerInterval = -1;
	spawnTimer->Start(spawnTimerInterval);
	spawnTimerInterval = -1;
	nocointimer->Start(nocointimerInterval);
	nocointimerInterval = -1;
	pause = false;
}

void MapGame::drawCooldown(wxBufferedPaintDC& pdc)
{
	auto current = clock();
	double snowPercent = max(0.0, (30.0 - ((double)(clock() - snowCD) / CLOCKS_PER_SEC)) / 30.0);
	double meteorPercent = max(0.0, (30.0 - ((double)(clock() - meteorCD) / CLOCKS_PER_SEC)) / 30.0);
	double wallPercent = max(0.0, (30.0 - ((double)(clock() - wallCD) / CLOCKS_PER_SEC)) / 30.0);
	double afterCalcSnow = (snowPercent == 0.0) ? 1 : snowPercent;
	double afterCalcMeteor = (meteorPercent == 0.0) ? 1 : meteorPercent;
	double afterCalcWall = (wallPercent == 0.0) ? 1 : wallPercent;
	double w1 = skillButton[0].x2 - skillButton[0].x1;
	double w2 = skillButton[1].x2 - skillButton[1].x1;
	double w3 = skillButton[2].x2 - skillButton[2].x1;
	wxGraphicsContext *gc = wxGraphicsContext::Create(pdc);
	if (gc)
	{
		//gc->SetPen(*wxWHITE_PEN);
		gc->SetBrush(wxColor(0, 0, 0, 200));
		wxGraphicsPath path = gc->CreatePath();
		if (snowPercent != 0.0)
			path.AddRectangle(skillButton[0].x1, skillButton[0].y1, skillButton[0].x2 - skillButton[0].x1, skillButton[0].y2 - skillButton[0].y1);
		if (meteorPercent != 0.0) 
			path.AddRectangle(skillButton[1].x1, skillButton[1].y1, skillButton[1].x2 - skillButton[1].x1, skillButton[1].y2 - skillButton[1].y1);
		if (wallPercent != 0.0)
			path.AddRectangle(skillButton[2].x1, skillButton[2].y1, skillButton[2].x2 - skillButton[2].x1, skillButton[2].y2 - skillButton[2].y1);
		gc->FillPath(path);
		gc->StrokePath(path);
		delete gc;
	}
	pdc.SetBrush(wxBrush((wxTransparentColor), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawRectangle(wxPoint(skillButton[0].x1, skillButton[0].y1 + 80), wxSize(w1, 10));
	pdc.SetBrush(wxColor(255, 255, 51));
	pdc.DrawRectangle(wxPoint(skillButton[0].x1, skillButton[0].y1 + 80), wxSize(w1 * afterCalcSnow, 10));
	pdc.SetBrush(wxBrush((wxTransparentColor), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawRectangle(wxPoint(skillButton[1].x1, skillButton[1].y1 + 80), wxSize(w2, 10));
	pdc.SetBrush(wxColor(255, 255, 51));
	pdc.DrawRectangle(wxPoint(skillButton[1].x1, skillButton[1].y1 + 80), wxSize(w2 * afterCalcMeteor, 10));
	pdc.SetBrush(wxBrush((wxTransparentColor), wxBRUSHSTYLE_TRANSPARENT));
	pdc.DrawRectangle(wxPoint(skillButton[2].x1, skillButton[2].y1 + 80), wxSize(w3, 10));
	pdc.SetBrush(wxColor(255, 255, 51));
	pdc.DrawRectangle(wxPoint(skillButton[2].x1, skillButton[2].y1 + 80), wxSize(w3 * afterCalcWall, 10));
}

User * MapGame::getUser()
{
	return user;
}

void MapGame::drawHealthBar(wxBufferedPaintDC &pdc) {

	wxFont fontNama(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	animationMinusHealthBar();
	pdc.SetFont(fontNama);
	pdc.DrawText(to_string(user->money), wxPoint(coinSize.GetWidth(), coinSize.GetHeight() + 20));
	pdc.SetBrush(wxBrush(wxColour(0, 0, 0), wxBRUSHSTYLE_TRANSPARENT));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawText(user->nama, 5, 5);
	pdc.DrawRoundedRectangle(5, wxGetDisplaySize().GetHeight() / 35, wxGetDisplaySize().GetWidth() / 3, 20, 3);
	pdc.SetBrush(wxBrush(wxColour(255 * (user->maxLifePoint - user->lifePoint) / user->maxLifePoint, 255 * user->lifePoint / user->maxLifePoint, 0)));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawText(user->nama, 5, 5);
	pdc.DrawRoundedRectangle(5, wxGetDisplaySize().GetHeight() / 35, user->lifePoint*(wxGetDisplaySize().GetWidth() / 3) / user->maxLifePoint, 20, 3);
	pdc.DrawText("Score: " + to_string(user->score), 5, wxGetDisplaySize().GetHeight() / 35 + 25);
}

void MapGame::drawPlaceholderTower(wxBufferedPaintDC & pdc)
{
	wxMouseState mouse = wxGetMouseState();
	if (activeButton != nullptr) {
		activeButton->drawPlaceholder(pdc, mouse);
	}
}

