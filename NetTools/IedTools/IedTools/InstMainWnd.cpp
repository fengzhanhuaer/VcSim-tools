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
		IedToolMsgCtrl ctrl;
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
		str << "初始化";
	}
	else if (Task::TaskStep() == DbgClient::E_WaitConnect)
	{
		str << "等待建立链接···";
	}
	else if (Task::TaskStep() == DbgClient::E_AskConnect)
	{
		str << "申请链接···";
	}
	else if (Task::TaskStep() == DbgClient::E_LogOn)
	{
		str << "正在登录···";
	}
	else if (Task::TaskStep() == DbgClient::E_AskIniInfo)
	{
		str << "索要信息···";
	}
	else if (Task::TaskStep() == DbgClient::E_Work)
	{
		str << "已连接";
	}
	else if (Task::TaskStep() == DbgClient::E_Check)
	{
		str << "自检···";
	}
	m_statusBar1->SetStatusText(str, 0);


}

void InstMainWnd::LogOnWnd(InstLogOnEvent& event)
{
	if (needLog)
	{
		InstLogOnWnd* w = new InstLogOnWnd(this, event.isCheckId, event.isCheckAccount, event.Id, event.Name, event.Pw);
		w->ShowModal();
		needLog = 0;

		while (LogStatus() == DbgClient::E_CheckPw)
		{
			Sleep(100);
		}
		uint8 status = LogStatus();
		if (status == DbgClient::E_LogOnIdErr)
		{
			wxMessageDialog dia(0, "唯一性代码不正确");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnAccountErr)
		{
			wxMessageDialog dia(0, "帐号或密码错误");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnAccountLock)
		{
			wxMessageDialog dia(0, "帐号已锁定，请稍后再试");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOnLinkErr)
		{
			wxMessageDialog dia(0, "网络连接异常");
			dia.ShowModal();
		}
		else if (status == DbgClient::E_LogOverTime)
		{
			wxMessageDialog dia(0, "登录超时");
			dia.ShowModal();
		}
	}
}

void InstMainWnd::ShowAbout(wxCommandEvent& event)
{
	wxMessageDialog dig(this, "iESLab, All Rights Reserved.\n冯占华\n V0.5.0\n" __DATE__" " __TIME__, "关于", wxOK);
	dig.ShowModal();
	event.Skip(0);
}

int32 InstMainWnd::RecMsg(SalCmmMsgHeader& msg)
{
	if (recvSem.Wait(200) < 0)
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

int32 InstMainWnd::SendMsg(SalCmmMsgHeader& msg)
{
	if (gmsock.IsLinkOk() == 0)
	{
		return 0;
	}
	if (sendSem.Wait(200) < 0)
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

int32 InstMainWnd::SendMsg(IedToolsMsgHeader& msg)
{
	msg.salHeader.len = (uint16)msg.dataLen + sizeof(SalTransHeader);
	return SendMsg(msg.salHeader);
}

void InstMainWnd::UpdateTitle()
{

}

void InstMainWnd::UpdateTime()
{
	String1000B str;
	iedStauts.stamp.ToStrHzFmt3(str);
	str << " ";
	str.FormatHex((uint8)iedStauts.stamp.q.q);
	m_statusBar1->SetStatusText(str.Str(), 1);
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
		checkTimer.UpCnt(5000);
		checkTimer.Enable(1);
	}
	else
	{
		checkTimer.Enable(0);
		return -1;
	}
	if (checkTimer.Status())
	{
		IedToolMsgCtrl ctrl;
		ctrl.SetMsgIniInfo(E_ITMT_SockClose, 0);
		SendMsg(ctrl.Header());
		MsSleep(100);
		CloseSock();
		LogMsg.Stamp() << "IedTools 心跳超时 关闭连接.\n";
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
	IedToolsMsg60kb imsg;
	if (RecMsg(imsg.header) <= 0)
	{
		MsSleep(10);
		return 0;
	}
	IedToolsMsgHeader* msg = (IedToolsMsgHeader*)&imsg;
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
		LogMsg.Stamp() << "IedTools Client ask 关闭连接.\n";
		break;
	}
	case E_ITMT_AskClientInfoAck:
	{
		IedToolsMsg* m = (IedToolsMsg*)msg;
		TransString ts;
		ts.SetBuf((const char*)m->data);
		CallAfter(&InstMainWnd::UpdateTitle);
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
	ClientPort.Set("ClientPort", "Client端口33001~35000", 33100);
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

