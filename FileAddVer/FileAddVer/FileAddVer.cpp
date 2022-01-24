#include "FileAddVer.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	MainWndInst* wnd = new MainWndInst();
	wnd->Show();
	return true;
}
