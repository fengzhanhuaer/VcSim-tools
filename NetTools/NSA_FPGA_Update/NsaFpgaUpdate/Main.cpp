#include "Main.h"
#include <tlhelp32.h>
IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;
	instwnd = new InstMainWnd();
	instwnd->Show();
	return true;
}

MainApp::~MainApp()
{

}

