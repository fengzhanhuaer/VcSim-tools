#pragma once
#include"FmtSv2FpgaBin.h"

class InstMainWnd :public MainWnd
{
public:
	InstMainWnd();
	virtual void FmtSv2FpgaBin(wxCommandEvent& event);
};
