#pragma once
#include"MainWnd.h"


class InstDbgCfg : public DbgClientCfg
{
public:
	int32 PowerUpIni(int32 Para);
public:
private:
};

class InstLogOnEvent :public wxEvent
{
public:
	InstLogOnEvent(wxEventType eventType, int winid, bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw)
		: isCheckId(isCheckId), isCheckAccount(isCheckAccount), Id(Id), Name(Name), Pw(Pw), wxEvent(winid, eventType)
	{

	}
	virtual wxEvent* Clone() const
	{
		return new InstLogOnEvent(*this);
	}
public:
	bool8 isCheckId;
	bool8 isCheckAccount;
	SalString& Id;
	SalString& Name;
	SalString& Pw;
};


wxDECLARE_EVENT(Inst_LogOn_Event, InstLogOnEvent);
typedef void(wxEvtHandler::* InstLogOnEventFunc)(InstLogOnEvent&);
#define wxTransLogOnEventHandler(func) wxEVENT_HANDLER_CAST(InstLogOnEventFunc,func)

class InstMainWnd :public MainWnd, public DbgClient
{
public:
	struct IedStatus
	{
		SalDateStamp stamp;
	};
public:
	void ReConnect();
	int32 PowerUpIni(int32 Type);
	virtual int32 OneLoop();
	M_DynSingleton(InstMainWnd);
	virtual void LinkServer(wxCommandEvent& event);
	virtual bool8 AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)());
	virtual void StatusUpdate(wxTimerEvent& event);
	virtual void OnWndIdle(wxIdleEvent& event);
	virtual void LogOnWnd(InstLogOnEvent& event);
	virtual void ShowAbout(wxCommandEvent& event);
	int32 RecMsg(SalCmmMsgHeader& msg);
	int32 SendMsg(SalCmmMsgHeader& msg);
	int32 SendMsg(SalCmmMsgHeader& msg, uint32 DataLen);
	int32 SendMsg(IedToolsMsgHeader& msg);
	void UpdateTitle();
	void UpdateTime();
protected:
	int32 Check();
	int32 Work();
	int32 CloseSock();
	InstMainWnd();
	~InstMainWnd();
public:
	InstDbgCfg& DbgCfg() { return dbgcfg; };
protected:
	MsTimer checkTimer;
	MsTimer heartbeatTimer;
	InstDbgCfg dbgcfg;
	bool8 needLog;
	uint8 lastSec;
	SemaphoreB sendSem;
	SemaphoreB recvSem;
	uint32 recMsgOkCnt;
	uint32 recMsgLastOkCnt;
	uint32 recMsgErrCnt;
	uint32 sendMsgOkCnt;
	uint32 sendMsgErrCnt;
	IedStatus iedStauts;
};
class InstLogOnWnd :public LogWnd
{
public:
	InstLogOnWnd(wxWindow* parent, bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw)
		:LogWnd(parent), Id(Id), Name(Name), Pw(Pw)
	{
		this->isCheckId = isCheckId;
		this->isCheckAccount = isCheckAccount;
		if (!isCheckId)
		{
			LogBox->Hide((size_t)0);
		}
		if (!isCheckAccount)
		{
			LogBox->Hide((size_t)1);
		}
	}
	virtual void Enter(wxCommandEvent& event)
	{
		event.Skip(0);
		Id = idtext->GetValue();
		Name = nametext->GetValue();
		Pw = pwtext->GetValue();
		Close(1);
	}
	virtual void Cancel(wxCommandEvent& event)
	{
		event.Skip(0);
		Close(1);
	}
	bool8 isCheckId;
	bool8 isCheckAccount;
	SalString& Id;
	SalString& Name;
	SalString& Pw;
};