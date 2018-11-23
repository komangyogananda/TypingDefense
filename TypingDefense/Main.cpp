#include "wx\wx.h"
#include "Frame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)
DECLARE_APP(MyApp)

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler);
	Frame *frame = new Frame("Typing Defense");
	return true;
}