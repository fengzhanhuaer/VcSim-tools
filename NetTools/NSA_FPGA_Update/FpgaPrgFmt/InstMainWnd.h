#pragma once
#include"FpgaPrgFmt.h"

class InstMainWnd :public MainWnd
{
public:
	InstMainWnd();
	virtual void OpenPrg(wxCommandEvent& event);
	virtual void CreatPrg(wxCommandEvent& event);
	virtual void CheckPrg(wxCommandEvent& event);
	void LogMsg(const char* Msg);
protected:
	wxString path;
	wxString dir;
};
