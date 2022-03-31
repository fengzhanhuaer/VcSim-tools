#include"Main.h"

wxDEFINE_EVENT(Inst_LogOn_Event, InstLogOnEvent);

InstMainWnd::InstMainWnd()
	:MainWnd(0)
{
	cfg = &dbgcfg;
	this->Connect(Inst_LogOn_Event, wxTransLogOnEventHandler(InstMainWnd::LogOnWnd));
}

InstMainWnd::~InstMainWnd()
{
	SocketEnvClearUp();
	this->Disconnect(Inst_LogOn_Event, wxTransLogOnEventHandler(InstMainWnd::LogOnWnd));
}

void InstMainWnd::ReConnect()
{
	DbgClient::ReConnect();
}

int32 InstMainWnd::PowerUpIni(int32 Type)
{
	recvSem.Creat(1);
	sendSem.Creat(1);
	dbgcfg.PowerUpIni(0);
	if (dbgcfg.EnableGmCrtCheck.Data())
	{
		CheckDbgClientCrt();
	}
	SocketEnvStartUp();
	SptMsInt::Instance().PowerUpIni(2);
	SptDateTask::Instance().PowerUpIni(2);
	DbgClient::PowerUpIni(0);
	ServerIp->SetValue(dbgcfg.ServerIp.StrData());
	wxScreenDC dc;
	dc.SetFont(m_statusBar1->GetFont());
	wxString tempString('M', 1);
	wxCoord width, height;
	dc.GetTextExtent(tempString, &width, &height);
	int fildw[5] = { width * 10,width * 20, };
	m_statusBar1->SetStatusWidths(WXSIZEOF(fildw), fildw);
	Start();
	return 0;
}

int32 InstMainWnd::OneLoop()
{
	switch (taskStep)
	{
	case DbgClient::E_PowerUpIni:
	{
		OneLoopPowerUpIni();
		break;
	}
	case DbgClient::E_ClentIni:
	{
		ClientIni();
		break;
	}
	case E_WaitConnect:
	{
		WaitConnect();
		break;
	}
	case DbgClient::E_AskConnect:
	{
		AskConnect(DbgToolsServer::E_IedTools);
		break;
	}
	case DbgClient::E_LogOn:
	{
		if (0 == StartClient(DbgToolsServer::E_IedTools, signIn.LocalIp().u32, signIn.LocalPort().u16, signIn.RemoteIp().u32, signIn.RemotePort().u16, signIn.ClientSock()))
		{
			taskStep = E_AskIniInfo;
			GraphicDevice::Instance().ClearAll();
		}
		else
		{
			taskStep = E_ClentIni;
		}
		break;
	}
	case E_AskIniInfo:
	{
		SalTransFrame5kB ctrl;
		ctrl.SetMsgIniInfo(E_ITMT_AskClientInfo, 0);
		SendMsg(ctrl.Header());
		taskStep = E_Work;
		break;
	}
	case E_Work:
	{
		Work();
		taskStep = E_Check;
		break;
	}
	case E_Check:
	{
		if (Check() >= 0)
		{
			taskStep = E_Work;
		}
		else
		{
			taskStep = E_WaitConnect;
		}
		break;
	}
	default:
		taskStep = E_ClentIni;
		break;
	}
	return 0;
}

void InstMainWnd::LinkServer(wxCommandEvent& event)
{
	event.Skip(0);
	String100B cstr;
	cstr = ServerIp->GetValue().c_str();
	if (cstr != dbgcfg.ServerIp.StrData())
	{
		dbgcfg.ServerIp.SetData(cstr.Str());
		dbgcfg.SaveAll();
	}
	ReConnect();
}

bool8 InstMainWnd::AskForLogOnInfo(bool8 isCheckId, bool8 isCheckAccount, SalString& Id, SalString& Name, SalString& Pw, int32(*DoHeartCheck)())
{
	InstLogOnEvent* event = new InstLogOnEvent(Inst_LogOn_Event, wxID_ANY, isCheckId, isCheckAccount, Id, Name, Pw);
	event->SetEventObject(this);
	needLog = 1;
	QueueEvent(event);
	while (needLog)
	{
		SendLogHeartBeat();
		MsSleep(100);
	}
	return 0;
}

void InstMainWnd::StatusUpdate(wxTimerEvent& event)
{
	event.Skip(0);
}

void InstMainWnd::OnWndIdle(wxIdleEvent& event)
{
	wxString str;
	if (Task::TaskStep() == DbgClient::E_ClentIni)
	{
		str << "��ʼ��";
	}
	else if (Task::TaskStep() == DbgClient::E_WaitConnect)
	{
		str << "�ȴ��������ӡ�����";
	}
	else if (Task::TaskStep() == DbgClient::E_AskConnect)
	{
		str << "�������ӡ�����";
	}
	else if (Task::TaskStep() == DbgClient::E_LogOn)
	{
		str << "���ڵ�¼������";
	}
	else if (Task::TaskStep() == DbgClient::E_AskIniInfo)
	{
		str << "��Ҫ��Ϣ������";
	}
	else if (Task::TaskStep() == DbgClient::E_Work)
	{
		str << "������";
	}
	else if (Task::TaskStep() == DbgClient::E_Check)
	{
		str << "�Լ졤����";
	}
	m_statusBar1->SetStatusText(str, 0);


}

void InstMainWnd::LogOnWnd(InstLogOnEvent& event)
{
	if (needLog)
	{
		needLog = 0;
		if ((event.isCheckId || event.isCheckAccount) == 0)
		{
			return;
		}
		InstLogOnWnd* w = new InstLogOnWnd(this, event.isCheckId, event.isCheckAccount, event.Id, event.Name, event.Pw);
		w->ShowModal();
		while (LogStatus() == DbgClient::E_CheckPw)
		{
			Sleep(100);
		}
		uint8 status = LogStatus();
		if (status == DbgClient::E_LogOnIdErr)
		{
			wxMessageDialog dia(0, "Ψһ�Դ��벻��ȷ");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnAccountErr)
		{
			wxMessageDialog dia(0, "�ʺŻ��������");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnAccountLock)
		{
			wxMessageDialog dia(0, "�ʺ������������Ժ�����");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnLinkErr)
		{
			wxMessageDialog dia(0, "���������쳣");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOverTime)
		{
			wxMessageDialog dia(0, "��¼��ʱ");
			dia.ShowModal();
		}
	}
}

void InstMainWnd::ShowAbout(wxCommandEvent& event)
{
	wxMessageDialog dig(this, "iESLab, All Rights Reserved.\n��ռ��\n V0.5.0\n" __DATE__" " __TIME__, "����", wxOK);
	dig.ShowModal();
	event.Skip(0);
}

int32 InstMainWnd::RecMsg(SalCmmMsgHeader& msg)
{
	if (recvSem.Wait(1000) < 0)
	{
		return 0;
	}
	try
	{


		SalCmmMsgHeader header;
		int cnt = 0;
		while (gmsock.Recv(&header, sizeof(header), 0) == sizeof(header))
		{
			if (header.header == 0xd555)
			{
				MemCpy(&msg, &header, sizeof(header));
				int len = msg.len - sizeof(header) + sizeof(DbgMsg::checkCode);
				int32 remLen = 0;
				int32 recLen = 0;
				int32 breakcnt = 0;
				do
				{
					recLen += remLen = gmsock.Recv(((uint8*)&msg) + sizeof(SalCmmMsgHeader), len - recLen, 0);
					if (remLen < 0)
					{
						breakcnt++;
						if (breakcnt > 5)
						{
							break;
						}
					}
					else
					{
						breakcnt = 0;
					}
					MsSleep(10);
				} while (recLen < len);
				if (recLen == len)
				{
					if (msg.IsCrcOk())
					{
						recvSem.Post();
						recMsgOkCnt++;
						return  msg.len;
					}
					recMsgErrCnt++;
				}
				else
				{
					recMsgErrCnt++;
					recvSem.Post();
					return -1;
				}
			}
			else
			{
				cnt++;
				if (cnt > 10)
				{
					recvSem.Post();
					return -1;
				}
			}
		}
		recvSem.Post();
	}
	catch (...)
	{
		recvSem.Post();
	}
	return 0;
}

int32 InstMainWnd::RecMsg(uint32 MsgType, int32 WaitTime, SalCmmMsgHeader& Msg)
{
	if (gmsock.IsLinkOk() == 0)
	{
		return -1;
	}
	MsTimer timer;
	timer.UpCnt(WaitTime);
	timer.Enable(1);
	SalTransHeader* msg = (SalTransHeader*)&Msg;
	while (!timer.Status())
	{
		if (RecMsg(Msg) <= 0)
		{
			MsSleep(200);
			SendHeartBeat();
		}
		else if (msg->type == MsgType)
		{
			return 0;
		}
	}
	return -1;
}

int32 InstMainWnd::SendMsg(SalCmmMsgHeader& msg)
{
	if (gmsock.IsLinkOk() == 0)
	{
		return 0;
	}
	if (sendSem.Wait(1000) < 0)
	{
		return 0;
	}
	msg.header = 0xd555;
	msg.type = SCT_IEDTools;
	msg.sur = gmsock.LocalIp().u2b[1].u16;
	msg.dst = gmsock.RemoteIp().u2b[1].u16;
	msg.AddCrc();
	try
	{
		gmsock.Send(&msg, msg.len + sizeof(SalCmmMsg<2>::checkCode), 0);
	}
	catch (...)
	{

	}
	sendSem.Post();
	sendMsgOkCnt++;
	return msg.len;
}

int32 InstMainWnd::SendMsg(SalCmmMsgHeader& msg, uint32 DataLen)
{
	msg.len = (uint16)DataLen + sizeof(msg.header);
	return SendMsg(msg);
}

int32 InstMainWnd::SendMsg(SalTransHeader& msg)
{
	msg.salHeader.len = (uint16)msg.dataLen + sizeof(SalTransHeader);
	return SendMsg(msg.salHeader);
}

void InstMainWnd::UpdateTitle()
{
	wxString str = "IedTools ";
	str += iedStauts.iedName;
	str += " - ";
	str += iedStauts.iedType;
	str += " - ";
	str += iedStauts.iedDiviceId;
	SetTitle(str);
}

void InstMainWnd::UpdateTime()
{
	String1000B str;
	iedStauts.stamp.ToStrHzFmt3(str);
	str << " ";
	str.FormatHex((uint8)iedStauts.stamp.q.q);
	m_statusBar1->SetStatusText(str.Str(), 1);
}

void InstMainWnd::ShowDiglog(SalTransFrame60kB* msg)
{
	uint32 type;
	msg->Read(type);
	if (type == IedToolsDialog::E_AskIdPw)
	{
		char title[40];
		char name[40];
		msg->Read(title, sizeof(title));
		msg->Read(name, sizeof(name));
		String100B Id;
		String100B Name;
		String100B Pw;
		InstLogOnWnd* wnd = new InstLogOnWnd(this, 0, 1, Id, Name, Pw);
		wnd->SetTitle(title);
		wnd->ShowModal();
		SalTransFrame5kB sendmsg;
		sendmsg.SetMsgIniInfo(E_ITMT_ShowDialog, 0);
		uint32 u32 = IedToolsDialog::E_AskIdPw;
		sendmsg.Write(&u32, sizeof(u32));
		if (wnd->isOk)
		{
			int32 i32 = 0;
			sendmsg.Write(&i32, sizeof(i32));
			char buf[40];
			StrNCpy(buf, Name.Str(), sizeof(buf));
			DecryptData(buf, sizeof(buf), 156);
			sendmsg.Write(&buf, sizeof(buf));
			StrNCpy(buf, Pw.Str(), sizeof(buf));
			DecryptData(buf, sizeof(buf), 156);
			sendmsg.Write(&buf, sizeof(buf));
		}
		else
		{
			int32 i32 = -1;
			sendmsg.Write(&i32, sizeof(i32));
		}
		SendMsg(sendmsg.Header());
	}
	delete msg;
}

void InstMainWnd::SendHeartBeat()
{
	SalDateStamp s;
	s.Now();
	IedToolHeartBeatMsg msg;
	msg.data.stamp = s;
	msg.header.SetHeader(E_ITMT_HeartBeat, 0, sizeof(msg.data));
	SendMsg(msg.header.salHeader);
	heartbeatTimer.Restart();
}

int32 InstMainWnd::Check()
{
	if (checkTimer.IsEnable())
	{
		if (recMsgLastOkCnt != recMsgOkCnt)
		{
			checkTimer.Restart();
		}
		recMsgLastOkCnt = recMsgOkCnt;
	}
	else if (gmsock.IsLinkOk())
	{
		checkTimer.UpCnt(10000);
		checkTimer.Enable(1);
	}
	else
	{
		checkTimer.Enable(0);
		return -1;
	}
	if (checkTimer.Status())
	{
		SalTransFrame5kB ctrl;
		ctrl.SetMsgIniInfo(E_ITMT_SockClose, 0);
		SendMsg(ctrl.Header());
		MsSleep(100);
		CloseSock();
		LogMsg.Stamp() << "IedTools ������ʱ �ر�����.\n";
		return -1;
	}
	if (heartbeatTimer.IsEnable())
	{
		if (heartbeatTimer.Status())
		{
			SalDateStamp s;
			s.Now();
			uint8  now = (uint8)(s.Us() / s.Dt1Second);
			if (lastSec != now)
			{
				IedToolHeartBeatMsg msg;
				msg.data.stamp = s;
				msg.header.SetHeader(E_ITMT_HeartBeat, 0, sizeof(msg.data));
				SendMsg(msg.header.salHeader);
				heartbeatTimer.Restart();
				lastSec = now;
			}
		}
	}
	else
	{
		heartbeatTimer.UpCnt(500);
		heartbeatTimer.Enable(1);
	}
	return 0;
}

int32 InstMainWnd::Work()
{
	SalTransFrame5kB imsg;
	if (RecMsg(imsg.Header().salHeader) <= 0)
	{
		MsSleep(10);
		return 0;
	}
	Unpack(imsg.Header().salHeader);
	return 0;
}

int32 InstMainWnd::Unpack(SalCmmMsgHeader& Msg)
{
	SalTransHeader* msg = (SalTransHeader*)&Msg;
	uint16 type = msg->type;
	switch (type)
	{
	case E_ITMT_HeartBeat:
	{
		IedToolHeartBeatMsg m;
		MemCpy(&m, msg, msg->salHeader.len);
		iedStauts.stamp = m.data.stamp;
		CallAfter(&InstMainWnd::UpdateTime);
		break;
	}
	case E_ITMT_SockClose:
	{
		CloseSock();
		LogMsg.Stamp() << "IedTools Client ask �ر�����.\n";
		break;
	}
	case E_ITMT_AskClientInfoAck:
	{
		SalTransFrame* m = (SalTransFrame*)msg;
		TransString ts;
		String100B str;
		ts.SetBuf((const char*)m->data);
		ts.GetLine(str, ',');
		iedStauts.iedName = str.Str();
		str.Clear();
		ts.GetLine(str, ',');
		iedStauts.iedType = str.Str();
		str.Clear();
		ts.GetLine(str, ',');
		iedStauts.iedDiviceId = str.Str();
		str.Clear();
		CallAfter(&InstMainWnd::UpdateTitle);
		SalTransFrame5kB ctrl;
		ctrl.SetMsgIniInfo(E_ITMT_AskRootWnd, 0);
		SendMsg(ctrl.Header());
		break;
	}
	case E_ITMT_ShowDialog:
	{
		SalTransFrame60kB* m = new SalTransFrame60kB;
		MemCpy(m, msg, msg->dataLen);
		CallAfter(&InstMainWnd::ShowDiglog, m);
		break;
	}
	default:
		break;
	}
	return 0;
}

int32 InstMainWnd::CloseSock()
{
	gmsock.Close();
	String100B str;
	gmsock.GetRemote(str);
	DbgToolsServer::Instance().SetClientClose(DbgToolsServer::E_IedTools, str.Str());
	checkTimer.Enable(0);
	return 0;
}

int32 InstDbgCfg::PowerUpIni(int32 Para)
{
	ClientPort.Set("ClientPort", "Client�˿�33001~35000", 33100);
	DbgClientCfg::PowerUpIni(Para);
	DataNum = 0;
	AddCfgData(&ServerIp);
	AddCfgData(&ClientIp);
	AddCfgData(&ClientPort);
	AddCfgData(&EnableGmssl);
	AddCfgData(&EnableGmCrtCheck);
	AddCfgData(&GmsslVerifyMode);
	AddCfgData(&GmsslLinkMode);
	AddCfgData(&GmsslCrtFormat);
	path.Set(CN_CFG_FILE_ROOT);
	name.Set("IedTools.cfg");
	if ((uint32)ReadAll() != CfgDataNum())
	{
		SaveAll();
	}
	return 0;
}

