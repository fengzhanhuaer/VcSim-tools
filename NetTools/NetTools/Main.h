#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<pcap.h>
#include<wx/wx.h>
#include"ApiProject.h"
#include"PcapDes.h"
#include<vector>
#include"MainWnd.h"
#include"PcapDump.h"
class SptWxTreeItemData :public  wxTreeItemData
{
public:
	SptWxTreeItemData() { MemSet(&data, 0, sizeof(data)); }
	st64value& Data() { return data; };
protected:
	st64value data;
};
using namespace spt;
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
	bool OpenNetCard(pcap_if_t* NetDev);
	bool CloseNetCard();
	bool StartRecv(class RecvDriver* Driver);
	bool StopRecv(class RecvDriver* Driver);
	void Packet_Recv_Handler(MainApp* app, const struct pcap_pkthdr* header, const u_char* pkt_data);
	bool StartRecv();
	bool IsStartRecv() { return enableRecv; }
	~MainApp()
	{
		StopRecv();
	}
protected:
	bool StopRecv();
protected:
	class MainWndInst* Inst;
	pcap_if_t* netDev;
	pcap_t* adhandle;
	char pcap_if_t_name[512];
	bool enableRecv;
	class RecvDriver* RecvDriverFirst;
	Thread* packRecvThread;
};

DECLARE_APP(MainApp);
#include"GnrRecv.h"

class MainWndInst :public MainWnd
{
public:
	MainWndInst() :MainWnd(0) {
		curaddev = alladdevs = 0;
		refreshNetCard();
		RecvGnrPage1 = new RecvPageInst(recvBook);
		recvBook->AddPage(RecvGnrPage1, "通用1", 0);
		RecvGnrPage1->PowerUpIniTree();
		RecvGnrPage2 = new RecvPageInst(recvBook);
		recvBook->AddPage(RecvGnrPage2, "通用2", 0);
		RecvGnrPage2->PowerUpIniTree();
	}
	pcap_if_t* GetCurNetCard()
	{
		int sec = NetCard->GetSelection();
		if (sec < adNum)
		{
			pcap_if_t* d = alladdevs;
			for (int i = 0; i < adNum; i++)
			{
				if (i == sec)
				{
					return d;
				}
				if (d)
				{
					d = d->next;
				}
			}
		}
		return 0;
	}
	void SetInfo(const char* Info)
	{
		m_statusBar1->SetStatusText(Info);
	}
	virtual void OpenSvPcap2Bin(wxCommandEvent& event);
	virtual void SendEthnetFrame(wxCommandEvent& event);
protected:

	virtual void refreshNetCard(wxCommandEvent& event) {
		event.Skip(0);
		refreshNetCard();
	}
	virtual void WndClose(wxCloseEvent& event) {
		wxGetApp().CloseNetCard();
		event.Skip(1);
	}
	virtual void OpenNetCard(wxCommandEvent& event) {
		if (wxGetApp().IsStartRecv())
		{
			wxGetApp().CloseNetCard();
		}
		else
		{
			wxGetApp().OpenNetCard(GetCurNetCard());
		}
		if (wxGetApp().IsStartRecv())
		{
			m_button7->SetLabelText("关闭网口");
		}
		else
		{
			m_button7->SetLabelText("打开网口");
		}
		event.Skip(0);
	}
	void refreshNetCard() {
		char errbuf[PCAP_ERRBUF_SIZE + 1];
		char infobuf[PCAP_ERRBUF_SIZE + 1];
		adNum = 0;
		if (alladdevs)
		{
			pcap_freealldevs(alladdevs);
		}
		/* Retrieve the device list */
		if (pcap_findalldevs(&alladdevs, errbuf) == -1)
		{
			snprintf(infobuf, sizeof(infobuf), "Error: %s\n", errbuf);
			SetInfo(infobuf);
		}
		NetCard->Clear();
		/* Scan the list printing every entry */
		pcap_if_t* d;
		for (d = alladdevs; d; d = d->next)
		{
			NetCard->Insert(d->description, adNum);
			adNum++;
		}
		if (alladdevs)
		{
			curaddev = alladdevs;
			NetCard->SetSelection(0);
		}
	}
	~MainWndInst()
	{
		if (alladdevs)
		{
			pcap_freealldevs(alladdevs);
		}
	}
protected:
	RecvPageInst* RecvGnrPage1;
	RecvPageInst* RecvGnrPage2;
	pcap_if_t* alladdevs;
	pcap_if_t* curaddev;
	int adNum;
	bool sendEthFrame;
};

