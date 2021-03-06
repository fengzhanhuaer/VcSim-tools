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
class InstMsgEvent :public wxEvent
{
public:
	InstMsgEvent(wxEventType eventType, int winid, wxObject* obj, SalTransFrame60kB* Msg) : msg(Msg), wxEvent(winid, eventType) {
	}
	virtual wxEvent* Clone() const { return new InstMsgEvent(*this); }
public:
	SalTransFrame60kB* msg;
};


wxDECLARE_EVENT(Inst_LogOn_Event, InstLogOnEvent);
typedef void(wxEvtHandler::* InstLogOnEventFunc)(InstLogOnEvent&);
#define wxTransLogOnEventHandler(func) wxEVENT_HANDLER_CAST(InstLogOnEventFunc,func)
wxDECLARE_EVENT(Inst_Msg_Event, InstMsgEvent);
typedef void(wxEvtHandler::* InstMsgEventFunc)(InstMsgEvent&);
#define wxTransMsgEventHandler(func) wxEVENT_HANDLER_CAST(InstMsgEventFunc,func)

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
		if (Name.StrLen())
		{
			nametext->SetValue(Name.Str());
			nametext->SetEditable(0);
		}
		isOk = 0;
	}
	virtual void Enter(wxCommandEvent& event)
	{
		event.Skip(0);
		Id = idtext->GetValue();
		Name = nametext->GetValue();
		Pw = pwtext->GetValue();
		Close(1);
		isOk = 1;
	}
	virtual void Cancel(wxCommandEvent& event)
	{
		event.Skip(0);
		Close(1);
		isOk = 0;
	}
	bool8 isOk;
	bool8 isCheckId;
	bool8 isCheckAccount;
	SalString& Id;
	SalString& Name;
	SalString& Pw;
};
class InstCascadeWnd : public CascadeWnd
{
public:
	InstCascadeWnd(wxWindow* parent, class InstMainWnd* iInstMainWnd);
	virtual void PageChanged(wxListbookEvent& event);
	virtual void PageChanging(wxListbookEvent& event);
	uint32 parentWndId;
	uint32 wndId;
	InstMainWnd* instMainWnd;
};

class InstWhiteBoard : public WhiteBoard
{
public:
	InstWhiteBoard(wxWindow* parent, class InstMainWnd* iInstMainWnd, SalTransFrame256B* Ctrl);
	uint32 parentWndId;
	uint32 wndId;
	InstCascadeWnd* rootBook;
	InstMainWnd* instMainWnd;
};

class InstMainWnd :public MainWnd, public DbgClient
{
public:
	struct IedStatus
	{
		SalDateStamp stamp;
		uint32 Flag1Cnt;
		uint32 FlagCnt;
		wxString iedName;
		wxString iedType;
		wxString iedDiviceId;
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
	int32 RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& msg);
	int32 SendMsg(SalCmmMsgHeader& msg);
	int32 SendMsg(SalCmmMsgHeader& msg, uint32 DataLen);
	int32 SendMsg(SalTransHeader& msg);
	void UpdateTitle();
	void UpdateTime();
	void ShowDiglog(InstMsgEvent& event);
	void AddChildWnd(SalTransFrame256B* msg);
	void EnterWnd(SalTransFrame256B* msg);
	InstWhiteBoard* SearchBoard(InstCascadeWnd* RootBook, uint32 Id);
	void SendHeartBeat();
protected:
	int32 Check();
	int32 Work();
	int32 Unpack(SalCmmMsgHeader& msg);
	int32 CloseSock();
	InstMainWnd();
	~InstMainWnd();
public:
	InstDbgCfg& DbgCfg() { return dbgcfg; };
protected:
	InstCascadeWnd* rootBook;
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
