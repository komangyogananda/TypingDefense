#include "MapGame.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "Window.h"
#include "Frame.h"
#include <cctype>

BEGIN_EVENT_TABLE(MapGame, wxWindow)
	EVT_KEY_DOWN(MapGame::OnKeyDown)
	EVT_CHAR(MapGame::OnChar)
	EVT_TIMER(2000, MapGame::OnTimer)
	EVT_TIMER(2001, MapGame::QuestGiver)
	EVT_BUTTON(1003, MapGame::OnButtonClick)
	EVT_LEFT_DOWN(MapGame::OnClick)
	EVT_PAINT(MapGame::OnPaint)
END_EVENT_TABLE()

MapGame::MapGame(wxFrame * parent) : wxWindow(parent, wxID_ANY)
{
	this->SetFocus();
	quest = new Quest();
	user = new User("Your Name");
	user->lifePoint = 150;
	this->parent = parent;
	parent->GetSize(&w, &h);
	wxMessageOutputDebug().Printf("MAP GAME p %d %d\n", w, h);
	wxMessageOutputDebug().Printf("MAP GAME %d %d\n", w, h);
	this->SetSize(wxSize(w, h));

	timer = new wxTimer(this, 2000);
	timer->Start(5);

	questTimer = new wxTimer(this, 2001);
	questTimer->Start(2000);
	this->now = clock();
	
	backToMainMenu = new wxButton(this, 1003, wxT("Back To Main Menu"), wxPoint(w - 200, h - 200), wxDefaultSize);
	background = nullptr;
	mapStatusBar = new wxStatusBar(this->parent, -1);
	status = "default";
	this->parent->SetStatusBar(mapStatusBar);
	Monster *test = new Monster(this, 100, 100, 0, wxGetDisplaySize().GetHeight() / 2, 1);
	allMonster.push_back(test);

	Tower *tower = new BasicTower(1300, 450, allMonster, allBullet);
	allTower.push_back(tower);

	image = loadLogo(wxT("\\Map.png"));
	wxSize a = image.GetSize();
	double aspectRatio = (double)a.GetHeight() / a.GetWidth();
	image.Rescale(w, h, wxIMAGE_QUALITY_NORMAL);
	background = new wxBitmap(image);

	image = loadLogo(wxT("\\coin.png"));
	image.Rescale(100, image.GetHeight() * 100 / image.GetWidth());
	coin = new wxBitmap(image);
	
	image = loadLogo(wxT("\\snow.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	wxBitmap *skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	koordinatBox skillNow;
	skillNow.x1 = 3 * w / 4;
	skillNow.x2 = 3 * w / 4 + (image.GetWidth());
	skillNow.y1 = 9 * h / 10;
	skillNow.y2 = 9 * h / 10 + (image.GetHeight());
	skillButton.push_back(skillNow);
	
	image = loadLogo(wxT("\\meteor.png"));
	image.Rescale(image.GetWidth() / 2, image.GetHeight() / 2);
	skillCurr = new wxBitmap(image);
	skill.push_back(skillCurr);
	int next = 3 * w / 4 + image.GetWidth() + 10;
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

}

MapGame::~MapGame()
{
	delete background;
	delete backToMainMenu;
	delete timer;
	delete questTimer;
	//delete mapStatusBar;
}

wxImage MapGame::loadLogo(wxString path) {
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + path;
	wxImage image(fileLocation, wxBITMAP_TYPE_PNG);
	return image;
}

void MapGame::OnPaint(wxPaintEvent& event) {
	mapStatusBar->SetStatusText(status);
	mapStatusBar->Show(true);
	wxBufferedPaintDC pdc(this);
	
	pdc.DrawBitmap(*background, wxPoint(0, 0), true);
	pdc.DrawBitmap(*coin, wxPoint(9 * wxGetDisplaySize().GetWidth() / 10, 2));
	coinSize = wxSize(9 * wxGetDisplaySize().GetWidth() / 10 + coin->GetWidth() + 10, 2);

	for (int i = 0; i < skillButton.size(); i++) {
		pdc.DrawBitmap(*skill[i], wxPoint(skillButton[i].x1, skillButton[i].y1), true);
	}

	drawHealthBar(pdc);

	for (auto it = allMonster.begin(); it != allMonster.end(); it++) {
		int kondisi = (*it)->draw(pdc);
		if (kondisi != -1) {
			user->lifePoint -= (*it)->attackPoint;
			it = allMonster.erase(it);
			status = "y";
			if (it == allMonster.end()) break;
		}
	}

	for (auto it : allTower) {
		it->draw(pdc);
	}

	for (auto it = allBullet.begin(); it != allBullet.end(); it++) {
		int kondisi = (*it)->checkCollision();
		(*it)->draw(pdc);
		if (kondisi) {
			(*it)->giveDamage();
			it = allBullet.erase(it);
			if (it == allBullet.end()) break;
		}
	}

	if (!this->quest->getTarget().empty() && (this->quest)->check()) {
		user->money += (this->quest->getTarget()).size() * 5;
		(this->quest)->clearCurrent();
		(this->quest)->clearTarget();
		(this->quest)->clearLCP();
		questTimer->Start((rand() % 5 + 2) * 1000);
	}

	if (!this->quest->getTarget().empty()) {
		wxFont questFont(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
		pdc.SetFont(questFont);
		auto tnow = (double)(clock() - this->now) / CLOCKS_PER_SEC;
		tnow *= 1000;
		auto sec = (this->questInterval - tnow) / 1000;
		if (sec <= 0) {
			this->quest->clearCurrent();
			this->quest->clearTarget();
			this->quest->clearLCP();
			questTimer->Start((rand() % 5 + 2) * 1000);
		}
		pdc.DrawText((this->quest)->getCurrent(), wxPoint(100, wxGetDisplaySize().GetHeight() - 150));
		pdc.DrawText((this->quest)->getTarget(), wxPoint(100, wxGetDisplaySize().GetHeight() - 200));
		pdc.DrawText(to_string(sec) + " s" , wxPoint(100, wxGetDisplaySize().GetHeight() - 250));
		pdc.SetTextForeground(RGB(0, 255, 0));
		pdc.DrawText((this->quest)->getLCP(), wxPoint(100, wxGetDisplaySize().GetHeight() - 200));
		pdc.SetTextForeground(RGB(0, 0, 0));
	}

}

void MapGame::OnClick(wxMouseEvent & event)
{
	int x = event.GetX();
	int y = event.GetY();
	status = "outside";
	for (int i = 0; i < skillButton.size(); i++) {
		koordinatBox now = skillButton[i];
		wxMessageOutputDebug().Printf("x1 = %d y1 = %d x2 = %d y2 = %d", now.x1, now.y1, now.x2, now.y2);
		if (now.x1 <= x && x <= now.x2) {
			if (now.y1 <= y && y <= now.y2) {
				status = "Skill" + to_string(i + 1);
			}
		}
	}
}

void MapGame::OnButtonClick(wxCommandEvent & event)
{
	if (event.GetId() == 1003) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(1);
	}
}

void MapGame::OnTimer(wxTimerEvent &event) {
	for (auto it : allMonster) {
		it->jalan(1, 0);
	}
	Refresh(0);
}

void MapGame::OnKeyDown(wxKeyEvent & event)
{
	if (event.GetKeyCode() == WXK_BACK)
		(this->quest)->remCurrent();
	else event.Skip();
}

void MapGame::OnChar(wxKeyEvent & event)
{
	if (isprint(event.GetKeyCode()))
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
	this->questInterval = ((double)(this->quest->getTarget()).size()) / 5 * 1000;
	questTimer->Stop();
}

void MapGame::drawHealthBar(wxBufferedPaintDC &pdc) {

	wxFont fontNama(16, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	pdc.SetFont(fontNama);
	pdc.DrawText(to_string(user->money), wxPoint(coinSize.GetWidth(), coinSize.GetHeight()));
	pdc.SetBrush(wxBrush(wxColour(0, 0, 0), wxBRUSHSTYLE_TRANSPARENT));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawText(user->nama, 5, 5);
	pdc.DrawRoundedRectangle(5, wxGetDisplaySize().GetHeight() / 35, wxGetDisplaySize().GetWidth() / 3, 20, 3);
	pdc.SetBrush(wxBrush(wxColour(255 * (user->maxLifePoint - user->lifePoint) / user->maxLifePoint, 255 * user->lifePoint / user->maxLifePoint, 0)));
	pdc.SetPen(wxPen(wxColour(*wxWHITE)));
	pdc.DrawText(user->nama, 5, 5);
	pdc.DrawRoundedRectangle(5, wxGetDisplaySize().GetHeight() / 35,user->lifePoint*wxGetDisplaySize().GetWidth() / 3 / user->maxLifePoint, 20, 3);
	pdc.DrawText("Score: " + to_string(user->score), 5, wxGetDisplaySize().GetHeight() / 35 + 25);
}