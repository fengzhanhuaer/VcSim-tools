#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include"ApiProject.h"
using namespace spt;
#include<wx/wx.h>
#include<windows.h>  
#include"InstMainWnd.h"

class Thread :public wxThread
{
public:
	Thread(void(*CallBack)(void*), void* Para)
	{
		this->CallBack = CallBack;
		para = Para;
	}
	Thread(void* Para)
	{
		this->CallBack = 0;
		para = Para;
	}
	virtual void* Entry()
	{
		return DoWork();
	};
protected:
	virtual void* DoWork()
	{
		if (CallBack)
		{
			CallBack(para);
		}
		return 0;
	}
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

