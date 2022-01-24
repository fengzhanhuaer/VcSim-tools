#pragma once
#include"NetCapture.h"

struct GnrRecvWndData
{
	bool startRecv;
	pcap_if_t* curdev;
	pcap_t* adhandle;
	PcapDesFile desFile;
	EthFrameArray frameArray;
};
class SptWxTreeItemData :public  wxTreeItemData
{
public:
	SptWxTreeItemData() { MemSet(&data, 0, sizeof(data)); }
	st64value& Data() { return data; };
protected:
	st64value data;
};
class InstMainWnd :public MainWnd
{
public:
	InstMainWnd();
	~InstMainWnd();
	virtual void ReFreshGnrNetCard(wxCommandEvent& event);
	virtual void StartGnrCapture(wxCommandEvent& event);
	virtual void UpdateOnIdle(wxIdleEvent& event);
	virtual void UpDateUi10Ms(wxTimerEvent& event);
	virtual void ShowGnrSelFrame(wxGridEvent& event);
	virtual void ClearGnrFrame(wxCommandEvent& event);
	virtual void LoadGnrCfg(wxCommandEvent& event);
	virtual void SaveGnrPcap(wxCommandEvent& event);
protected:
	virtual void UpdateGnrFilter1(wxCommandEvent& event);
	virtual void UpdateGnrFilter2(wxCommandEvent& event);
	void LoadXmlNode(PcapDesNode* Node, wxTreeItemId& ParentId, wxTreeCtrl& treeView);
	void LoadXml(const char* FileName, PcapDesFile& desFile, wxTreeCtrl& treeView);
	void UpdateFrameGrid(GnrRecvWndData& data, wxGrid* grid);
	void SetInfo(const char* Info)
	{
		m_statusBar1->SetStatusText(Info);
	}
protected:
	GnrRecvWndData gnrRecvWndData;
};
