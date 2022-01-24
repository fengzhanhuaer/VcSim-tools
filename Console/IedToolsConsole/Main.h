#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<wx/wx.h>
#include<windows.h>  
#include"Console.h"

class Thread :public wxThread
{
public:
	Thread(void(*CallBack)(void*), void* Para)
	{
		this->CallBack = CallBack;
		para = Para;
	}
	virtual void* Entry()
	{
		CallBack(para);
		return 0;
	};
protected:
	void(*CallBack)(void*);
	void* para;

};
class MainApp : public wxApp
{
public:

public:
	virtual bool OnInit();
	~MainApp();
protected:
protected:
	InstMainWnd* instwnd;
};

DECLARE_APP(MainApp);

int StartOneInstWnd(const char* Path, const char* ProcessName, bool forceReStart);
