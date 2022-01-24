#include"Main.h"

InstMainWnd::InstMainWnd()
	:ConsoleWnd(0)
{
}

void InstMainWnd::OpenNgsSimLcd(wxCommandEvent& event)
{
	StartOneInstWnd(".\\", "SimLcd.exe", 1);
	event.Skip(0);
}

void InstMainWnd::OpenNgsVerAdd(wxCommandEvent& event)
{
	StartOneInstWnd(".\\", "FileAddVer.exe", 1);
	event.Skip(0);
}

void InstMainWnd::OpenGnrNetCapture(wxCommandEvent& event)
{
	StartOneInstWnd(".\\", "NetCapture.exe", 0);
	event.Skip(0);
}

void InstMainWnd::OpenNsaFpgaUpdate(wxCommandEvent& event)
{
	StartOneInstWnd(".\\", "NsaFpgaUpdate.exe", 0);
	event.Skip(0);
}
