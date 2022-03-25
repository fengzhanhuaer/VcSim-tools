#include "Main.h"
#include <tlhelp32.h>
IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	InstMainWnd::Instance().PowerUpIni(0);
	InstMainWnd::Instance().Show();
	return true;
}

MainApp::~MainApp()
{

}

