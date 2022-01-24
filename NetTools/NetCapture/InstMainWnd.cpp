#include"Main.h"

InstMainWnd::InstMainWnd()
	:MainWnd(0)
{
	gnrRecvWndData.adhandle = 0;
	gnrRecvWndData.curdev = 0;
	gnrRecvWndData.startRecv = 0;
	PcapDesFile& desFile = gnrRecvWndData.desFile;

	PcapDesNode* root = desFile.CreatNode(PcapDesNode::ClassName(), "Frame");
	desFile.AddNext(root);
	PcapDesNode* temp = desFile.CreatNode(PcapDesMacNode::ClassName(), "DstMac");
	root->AddChild(temp);

	temp = desFile.CreatNode(PcapDesMacNode::ClassName(), "SurMac");
	root->AddChild(temp);

	temp = desFile.CreatNode(PcapDesVlanNode::ClassName(), "VLan");
	root->AddChild(temp);

	temp = desFile.CreatNode(PcapHex16ValueNode::ClassName(), "EthType");
	temp->SetLittleEndian(0);
	root->AddChild(temp);
	String100B str;
	str << ".\\des\\" << "GnrFrame" << ".xml";
	desFile.SaveXml(str.Str());
	LoadXml(str.Str(), desFile, *m_treeCtrl1);

	wxCommandEvent event;
	ReFreshGnrNetCard(event);
}

void InstMainWnd::ReFreshGnrNetCard(wxCommandEvent& event)
{
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	char infobuf[PCAP_ERRBUF_SIZE + 1];
	pcap_if_t* alladdevs;
	pcap_if_t* curaddev;
	if (m_choice1->GetCount() > 0)
	{
		alladdevs = (pcap_if_t*)m_choice1->GetClientData();
		if (alladdevs)
		{
			pcap_freealldevs(alladdevs);
		}
	}
	/* Retrieve the device list */
	if (pcap_findalldevs(&alladdevs, errbuf) == -1)
	{
		snprintf(infobuf, sizeof(infobuf), "Error: %s\n", errbuf);
		SetInfo(infobuf);
	}
	m_choice1->Clear();
	/* Scan the list printing every entry */
	pcap_if_t* d;
	int i = 0;
	m_choice1->SetClientData(alladdevs);
	for (d = alladdevs; d; d = d->next)
	{
		m_choice1->Insert(d->description, i);
		i++;
	}
	if (alladdevs)
	{
		curaddev = alladdevs;
		m_choice1->SetSelection(0);
	}
	event.Skip(0);
}
InstMainWnd::~InstMainWnd()
{
	gnrRecvWndData.startRecv = 0;
}
void RecFrameFromEthCard(GnrRecvWndData* d)
{
	GnrRecvWndData& data = *(GnrRecvWndData*)d;
	while (1)
	{
		struct pcap_pkthdr* header;
		const u_char* pkt_data;
		EthFrameHdr hdr;
		if (data.startRecv && data.adhandle)
		{
			if (pcap_next_ex(data.adhandle, &header, &pkt_data) > 0)
			{
				hdr.hdr = *header;
				memcpy(&hdr.frame, pkt_data, header->caplen);
				if (data.desFile.Filter(hdr) == 1)
				{
					data.frameArray.push_back(hdr);
				}
			}
			else
			{
				MsSleep(1);
			}
		}
		else
		{
			break;
		}
	}
	if (data.adhandle)
	{
		pcap_close(data.adhandle);
	}
	return;
};
void InstMainWnd::StartGnrCapture(wxCommandEvent& event)
{
	event.Skip(0);
	GnrRecvWndData& data = gnrRecvWndData;
	wxChoice* choice = m_choice1;
	wxButton* btu = m_button2;
	if (data.startRecv == 0)
	{

		data.curdev = 0;
		data.startRecv = 0;
		pcap_if_t* dif = 0;
		int todev = choice->GetCount();
		if (todev > 0)
		{
			dif = (pcap_if_t*)choice->GetClientData();
			if (!dif)
			{
				return;
			}
		}
		else
		{
			return;
		}
		int sec = choice->GetSelection();
		pcap_if_t* d = dif;
		if (sec < todev)
		{
			for (int i = 0; i < todev; i++)
			{
				if (i == sec)
				{
					break;
				}
				if (d)
				{
					d = d->next;
				}
			}
		}
		else
		{
			return;
		}
		char errbuf[PCAP_ERRBUF_SIZE + 1];
		char infobuf[PCAP_ERRBUF_SIZE + 1];
		data.curdev = d;
		if ((data.adhandle = pcap_open_live(d->name, 65536, 1, 50, errbuf)) == 0)
		{
			snprintf(infobuf, sizeof(infobuf), "Error: %s\n", errbuf);
			SetInfo(infobuf);
		}
		else
		{
			snprintf(infobuf, sizeof(infobuf), "Open: %s\n", d->description);
			SetInfo(infobuf);
		}
		data.startRecv = 1;
		btu->SetLabel("结束");
		Thread* th = new  Thread((Thread::CallBack)RecFrameFromEthCard, &data);
		th->Create();
		th->SetPriority(WXTHREAD_DEFAULT_PRIORITY - 20);
		th->Run();
	}
	else
	{
		if (data.adhandle)
		{
			char infobuf[PCAP_ERRBUF_SIZE + 1];
			snprintf(infobuf, sizeof(infobuf), "Close: %s\n", data.curdev->description);
			SetInfo(infobuf);
		}
		data.curdev = 0;
		data.startRecv = 0;
		btu->SetLabel("开始");
	}
}
int dispGnrTreeNode(wxTreeCtrl* pRtFrameTree, PcapDesNode* Node)
{
	if (Node)
	{
		spt::String1kB Str;
		Str = Node->Des();
		Str << ":" << Node->FrmDes().Str();
		if (Node->UsrPri.value.vptr)
		{
			pRtFrameTree->SetItemText(Node->UsrPri.value.vptr, Str.Str());
		}
		if (Node->Child())
		{
			PcapDesNode* now = Node->Child();
			while (now)
			{
				dispGnrTreeNode(pRtFrameTree, now);
				now = now->Next();
			}
		}
	}
	return 0;
}
void InstMainWnd::ShowGnrSelFrame(wxGridEvent& event)
{
	int row = event.GetRow();
	wxGrid* grid = m_grid1;
	GnrRecvWndData& data = gnrRecvWndData;
	EthFrameHdr hdr = data.frameArray.at(row);
	data.desFile.Update(hdr);
	PcapDesNode* root = data.desFile.Root();
	if (root)
	{
		dispGnrTreeNode(m_treeCtrl1, root);
	}
	m_treeCtrl1->ExpandAll();
	String5000B str;
	for (size_t i = 0; i < hdr.hdr.caplen; i++)
	{
		str.FormatHex(hdr.frame.frameBuf[i]) << " ";
	}
	m_textCtrl5->SetLabelText(str.Str());

}

void InstMainWnd::UpdateOnIdle(wxIdleEvent& event)
{
	GnrRecvWndData& data = gnrRecvWndData;

	wxGrid* grid = m_grid1;
	if (data.frameArray.size())
	{
		int frameCnt = 0;
		bool stopUpdate = 0;
		if ((grid->GetNumberRows() < (int)data.frameArray.size()))
		{
			stopUpdate = 1;
			grid->BeginBatch();
		}
		while ((grid->GetNumberRows() < (int)data.frameArray.size()) && (frameCnt < 100))
		{
			frameCnt++;
			int row = grid->GetNumberRows();
			EthFrameHdr hdr = data.frameArray.at(row);
			SalDateStamp stamp;
			stamp.fromPriUtcCode(hdr.hdr.ts.tv_sec, hdr.hdr.ts.tv_usec << 8);
			grid->AppendRows();
			String5000B str;
			stamp.ToStrHzFmt3(str);
			grid->SetCellValue(row, 0, str.Str());
			str.Clear();
			str.FormatHex(hdr.frame.frameBuf[0]) << ".";
			str.FormatHex(hdr.frame.frameBuf[1]) << ".";
			str.FormatHex(hdr.frame.frameBuf[2]) << ".";
			str.FormatHex(hdr.frame.frameBuf[3]) << ".";
			str.FormatHex(hdr.frame.frameBuf[4]) << ".";
			str.FormatHex(hdr.frame.frameBuf[5]);
			grid->SetCellValue(row, 1, str.Str());
			str.Clear();
			str.FormatHex(hdr.frame.frameBuf[6]) << ".";
			str.FormatHex(hdr.frame.frameBuf[7]) << ".";
			str.FormatHex(hdr.frame.frameBuf[8]) << ".";
			str.FormatHex(hdr.frame.frameBuf[9]) << ".";
			str.FormatHex(hdr.frame.frameBuf[10]) << ".";
			str.FormatHex(hdr.frame.frameBuf[11]);
			grid->SetCellValue(row, 2, str.Str());
			str.Clear();
			uint16 data16 = GetEthnetType(hdr.frame.frameBuf);
			str.FormatHex(data16);
			grid->SetCellValue(row, 3, str.Str());
			str.Clear();
			str << hdr.hdr.caplen;
			grid->SetCellValue(row, 4, str.Str());
			str.Clear();
			for (size_t i = 0; i < hdr.hdr.caplen; i++)
			{
				str.FormatHex(hdr.frame.frameBuf[i]) << " ";
			}
			grid->SetCellValue(row, 6, str.Str());
			str.Clear();
		}
		if (stopUpdate)
		{
			grid->ScrollPages(1);
			grid->EndBatch();
		}
	}
	else
	{
		if (grid->GetNumberRows())
		{
			grid->DeleteRows(0, grid->GetNumberRows());
		}
	}
	event.Skip(0);
}

void InstMainWnd::UpdateFrameGrid(GnrRecvWndData& data, wxGrid* grid)
{

}

void InstMainWnd::ClearGnrFrame(wxCommandEvent& event)
{
	GnrRecvWndData& data = gnrRecvWndData;
	wxGrid* grid = m_grid1;
	grid->ClearGrid();
	data.frameArray.clear();
}

void InstMainWnd::LoadGnrCfg(wxCommandEvent& event)
{
	GnrRecvWndData& data = gnrRecvWndData;
	wxButton* btu = m_button2;
	if (data.adhandle && data.curdev)
	{
		char infobuf[PCAP_ERRBUF_SIZE + 1];
		snprintf(infobuf, sizeof(infobuf), "Close: %s\n", data.curdev->description);
		SetInfo(infobuf);
	}
	data.curdev = 0;
	data.startRecv = 0;
	btu->SetLabel("开始");
	wxFileDialog dia(this, "打开配置", ".\\des", "", "Files (*.xml)|*.xml", wxFD_OPEN);
	if (dia.ShowModal() == wxID_OK)
	{
		LoadXml(dia.GetPath(), data.desFile, *m_treeCtrl1);
	}
	event.Skip(0);
}

void InstMainWnd::SaveGnrPcap(wxCommandEvent& event)
{
	GnrRecvWndData& data = gnrRecvWndData;
	wxDateTime date;
	wxFileDialog dia(this, "保存报文", ".", "", "Files (*.cap)|*.cap", wxFD_SAVE);
	if (dia.ShowModal() == wxID_OK)
	{
		pcap_t* ad = pcap_open_dead(1, 65535);
		wxString name = dia.GetFilename();
		pcap_dumper_t* dumpfile = pcap_dump_open(ad, name);
		int32 num = data.frameArray.size();
		for (int32 i = 0; i < num; i++)
		{
			EthFrameHdr& hdr = data.frameArray.at(i);
			pcap_dump((u_char*)dumpfile, &hdr.hdr, &hdr.frame.frameBuf[0]);
		}
		pcap_dump_close(dumpfile);
		pcap_close(ad);
	}
	event.Skip(0);
}

void InstMainWnd::LoadXmlNode(PcapDesNode* Node, wxTreeItemId& ParentId, wxTreeCtrl& treeView)
{
	if (Node)
	{
		wxTreeItemId Id = treeView.AppendItem(ParentId, Node->Des());
		Node->UsrPri.value.vptr = Id;
		SptWxTreeItemData* data = new SptWxTreeItemData();
		data->Data().value.vptr = Node;
		m_choice2->Append(Node->Des(), Node);
		m_choice4->Append(Node->Des(), Node);
		treeView.SetItemData(Id, data);
		PcapDesNode* now = Node->Child();
		while (now)
		{
			LoadXmlNode(now, Id, treeView);
			now = now->Next();
		}
	}
}

void InstMainWnd::LoadXml(const char* FileName, PcapDesFile& desFile, wxTreeCtrl& treeView)
{
	m_choice2->Clear();
	m_choice4->Clear();
	treeView.DeleteAllItems();
	wxTreeItemId RootId = treeView.AddRoot("Info");
	desFile.LoadXml(FileName);
	PcapDesNode* root = desFile.Root();
	LoadXmlNode(root, RootId, treeView);
	treeView.ExpandAll();
	m_choice2->SetSelection(0);
	m_choice3->SetSelection(0);
	m_choice4->SetSelection(0);
	m_choice5->SetSelection(0);
}
void GnrChangeFilter(PcapDesNode* node, int Index, const char* Ctx)
{
	if (node)
	{
		if (StrLen(Ctx) > 0)
		{
			node->SetFilter(1, (PcapDesNode::FilterType)Index, Ctx);
		}
		else
		{
			node->SetFilter(0, (PcapDesNode::FilterType)Index, Ctx);
		}
	}
}
void InstMainWnd::UpdateGnrFilter2(wxCommandEvent& event)
{
	PcapDesNode* node = (PcapDesNode*)m_checkBox11->GetClientData();
	if (node)
	{
		node->SetFilter(0, (PcapDesNode::FilterType)0, 0);
	}
	event.Skip(0);
	node = (PcapDesNode*)m_choice4->GetClientData(m_choice4->GetSelection());
	GnrChangeFilter(node, m_choice5->GetSelection(), m_textCtrl4->GetLineText(0));
	m_checkBox1->SetClientData(node);
}

void InstMainWnd::UpdateGnrFilter1(wxCommandEvent& event)
{
	PcapDesNode* node = (PcapDesNode*)m_checkBox1->GetClientData();
	if (node)
	{
		node->SetFilter(0, (PcapDesNode::FilterType)0, 0);
	}
	event.Skip(0);
	node = (PcapDesNode*)m_choice2->GetClientData(m_choice2->GetSelection());
	GnrChangeFilter(node, m_choice3->GetSelection(), m_textCtrl1->GetLineText(0));
	m_checkBox11->SetClientData(node);
}
void InstMainWnd::UpDateUi10Ms(wxTimerEvent& event)
{
	event.Skip(0);
}