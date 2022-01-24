#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include"ApiProject.h"
#include"pcap.h"
#include"PcapDes.h"
#include<windows.h>  
#include<wx/wx.h>
#include"InstMainWnd.h"
using namespace spt;

class Thread :public wxThread
{
public:
	typedef void(*CallBack)(void*);
	Thread(CallBack cb, void* Para)
	{
		this->cb = cb;
		para = Para;
	}
	virtual void* Entry()
	{
		cb(para);
		Exit();
		return 0;
	};
protected:
	CallBack cb;
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
