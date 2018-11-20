#include "Window.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "MapGame.h"
#include "Frame.h"
#include<iostream>
using namespace std;
BEGIN_EVENT_TABLE(Window, wxWindow)
	EVT_BUTTON(1001, Window::OnButtonClick)
	EVT_BUTTON(1002, Window::OnButtonClick)
	EVT_PAINT(Window::OnPaint)
END_EVENT_TABLE()

Window::Window(wxFrame *parent) : wxWindow(parent, wxID_ANY)
{
	this->parent = parent;
	parent->GetSize(&width, &height);
	int w, h;
	this->GetSize(&w, &h);
	wxMessageOutputDebug().Printf("WINDOW p %d %d\n", width, height);
	wxMessageOutputDebug().Printf("WINDOW %d %d\n", w, h);
	this->SetSize(wxSize(width, height));
	wxButton *playGame = new wxButton(this, 1001, wxT("Play Game!"), wxPoint(width/2 - 40, height/2 - 10), wxDefaultSize);
	wxButton *highScore = new wxButton(this, 1002, wxT("High Score!"), wxPoint(width/2 - 40, height/2 + 30), wxDefaultSize);
	wxBitmap* logo = nullptr;
	this->SetBackgroundColour(wxColour(204, 172, 106));
	image = loadLogo();
}



Window::~Window()
{

}

wxImage Window::loadLogo() {
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);
	wxStandardPaths &stdPaths = wxStandardPaths::Get();
	wxString fileLocation = stdPaths.GetExecutablePath();
	fileLocation = wxFileName(fileLocation).GetPath() + wxT("\\logo1.png");
	wxImage image(fileLocation, wxBITMAP_TYPE_PNG);
	return image;
}

void Window::OnPaint(wxPaintEvent& event) {
	int w, h;
	parent->GetSize(&w, &h);
	wxSize a = image.GetSize();
	double aspectRatio = (double)a.GetHeight() / a.GetWidth();
	image.Rescale(480, 480*aspectRatio, wxIMAGE_QUALITY_NORMAL);
	logo = new wxBitmap(image);
	wxPaintDC pdc(this);
	if (logo != nullptr)
	{
		pdc.DrawBitmap(*logo, wxPoint((w /2) - (image.GetSize().GetWidth() / 2), (h / 2) - (image.GetSize().GetWidth() / 2) - 40), true);
	}
}

void Window::OnButtonClick(wxCommandEvent& event)
{
	if (event.GetId() == 1001) {
		Frame *currFrame = (Frame*)parent;
		currFrame->setCurrentWindow(2);
	}
	else if (event.GetId() == 1002) {
		wxMessageBox(wxT("High Score"));
	}
}
