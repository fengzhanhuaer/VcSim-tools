#pragma once
#include"ConsoleWnd.h"

class InstMainWnd :public ConsoleWnd
{
public:
	InstMainWnd();
	virtual void OpenNgsSimLcd(wxCommandEvent& event);
	virtual void OpenNgsVerAdd(wxCommandEvent& event);
	virtual void OpenGnrNetCapture(wxCommandEvent& event);
	virtual void OpenNsaFpgaUpdate(wxCommandEvent& event);
};
