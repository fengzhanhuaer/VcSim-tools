#pragma once

class RecvDriver
{
public:

public:
	RecvDriver() { next = 0; enRecv = 0; }
	virtual int Packet_Recv_Handler(RecvDriver* app, const struct pcap_pkthdr* header, const u_char* pkt_data) {
		RecvDriver* t = this;
		if (app != t)
		{
			return -1;
		}
		if (enRecv == 0)
		{
			return-1;
		}
		return header->len;
	}
public:
	PcapDesFile desFile;
	bool enRecv;
	unsigned int recvCnt;
	RecvDriver* next;
	std::vector<EthFrameHdr> frameArray;
};

class RecvPageInst :public recvPanel, public RecvDriver
{
public:
	RecvPageInst(wxWindow* Parent) :recvPanel(Parent)
	{
		FrameList->ClearAll();
		FrameList->InsertColumn(0, "序号");
		wxString str = "时间戳                         ";
		FrameList->InsertColumn(1, str);
		int w = FrameList->GetCharWidth();
		FrameList->SetColumnWidth(1, w * StrLen(str));
		str = "源地址               ";
		FrameList->InsertColumn(2, str, wxLIST_FORMAT_CENTRE);
		FrameList->SetColumnWidth(2, w * StrLen(str));
		str = "目的地址             ";
		FrameList->InsertColumn(3, str);
		FrameList->SetColumnWidth(3, w * StrLen(str));
		str = "类型       ";
		FrameList->InsertColumn(4, str);
		FrameList->SetColumnWidth(4, w * StrLen(str));
		str = "长度       ";
		FrameList->InsertColumn(5, str);
		FrameList->SetColumnWidth(5, w * StrLen(str));
		str = "备注       ";
		FrameList->InsertColumn(6, str);
		FrameList->SetColumnWidth(6, w * StrLen(str));
		str = "帧                                                                            ";
		FrameList->InsertColumn(7, str, wxLIST_FORMAT_RIGHT);
		FrameList->SetColumnWidth(7, w * StrLen(str));
		m_timer1.Start(1000);
		RtFrameText->GetStyle(0, FrameTextAtt);
		FrameTextAtt.SetBackgroundColour(*wxWHITE);

	};
	virtual void BtStartPcap(wxCommandEvent& event)
	{
		event.Skip(0);
		if (enRecv)
		{
			wxGetApp().StopRecv(this);
			BtStart->SetLabelText("开始");
		}
		else
		{
			wxGetApp().StartRecv(this);
			BtStart->SetLabelText("结束");
		}
	}
	virtual int Packet_Recv_Handler(RecvDriver* app, const struct pcap_pkthdr* header, const u_char* pkt_data)
	{
		if (RecvDriver::Packet_Recv_Handler(app, header, pkt_data) < 0)
		{
			return -1;
		}
		EthFrameHdr hdr;
		hdr.frameLen = header->caplen;
		hdr.hdr = *header;
		hdr.stamp.fromPriUtcCode(header->ts.tv_sec, header->ts.tv_usec << 8);
		int32 Len = Min(header->caplen, sizeof(hdr.frame));
		memcpy(&hdr.frame, pkt_data, Len);
		if (1 != desFile.Filter(hdr))
		{
			return -1;
		}
		frameArray.push_back(hdr);
		recvCnt++;
		wxString str;
		str << recvCnt;
		recvCntText->SetLabelText(str);
		ListCtrlAddFrame(hdr);
		return header->len;
	}
	virtual void ClearFrame(wxCommandEvent& event) {
		bool en = enRecv;
		enRecv = 0;
		MsSleep(1000);
		recvCnt = 0;
		frameArray.clear();
		FrameList->DeleteAllItems();
		MsSleep(100);
		wxString str;
		str << recvCnt;
		recvCntText->SetLabelText(str);
		event.Skip(0);
		enRecv = en;
	}
	virtual void FrameSelected(wxListEvent& event)
	{
		uint32 index = (uint32)event.GetIndex();
		if (index < frameArray.size())
		{
			DispHdrFrame(frameArray.at(index));
		}
		event.Skip(0);
	}
	virtual void ListCtrlAddFrame(EthFrameHdr& hdr)
	{
		wxString str;
		unsigned int index = FrameList->GetItemCount();
		str << index;
		FrameList->InsertItem(index, str);
		FrameList->SetItemData(index, index);
		String100B str1;
		hdr.stamp.ToStrHzFmt3(str1);
		FrameList->SetItem(index, 1, str1.Str());
		str1.Clear();
		str1.FormatHex(hdr.frame.st.sur[0]) << ":";
		str1.FormatHex(hdr.frame.st.sur[1]) << ":";
		str1.FormatHex(hdr.frame.st.sur[2]) << ":";
		str1.FormatHex(hdr.frame.st.sur[3]) << ":";
		str1.FormatHex(hdr.frame.st.sur[4]) << ":";
		str1.FormatHex(hdr.frame.st.sur[5]);
		FrameList->SetItem(index, 2, str1.Str());
		str1.Clear();
		str1.FormatHex(hdr.frame.st.dst[0]) << ":";
		str1.FormatHex(hdr.frame.st.dst[1]) << ":";
		str1.FormatHex(hdr.frame.st.dst[2]) << ":";
		str1.FormatHex(hdr.frame.st.dst[3]) << ":";
		str1.FormatHex(hdr.frame.st.dst[4]) << ":";
		str1.FormatHex(hdr.frame.st.dst[5]);
		FrameList->SetItem(index, 3, str1.Str());
		str1.Clear();
		uint16 type = ((hdr.frame.st.type[0] << 8) | hdr.frame.st.type[1]);
		if (type == 0x8100)
		{
			type = ((hdr.frame.st.type[4] << 8) | hdr.frame.st.type[5]);
		}
		str1.FormatHex(type);
		FrameList->SetItem(index, 4, str1.Str());
		str1.Clear();
		str1 << hdr.frameLen;
		FrameList->SetItem(index, 5, str1.Str());
		if (dispRtFrame->Get3StateValue() == wxCHK_CHECKED)
		{
			FrameList->ScrollLines(100);
		}
	}
	virtual void DispHdrFrame(EthFrameHdr& hdr)
	{
		if (IniTree)
		{
			String100B str;
			hdr.stamp.ToStrHzFmt3(str);
			wxString text;
			text = "Stamp:";
			text << str.Str();
			RtFrameTree->SetItemText(StampId, text);
			str.Clear();
			str << hdr.frameLen;
			text = "Length:";
			text << str.Str();
			RtFrameTree->SetItemText(LenId, text);
			desFile.Update(hdr);
			PcapDesNode* root = desFile.Root();
			if (root)
			{
				dispTreeNode(RtFrameTree, root);
			}
			RtFrameTree->ExpandAll();

		}
		if (1)
		{
			wxString str, temp;
			for (uint32 i = 1; i < hdr.frameLen + 1; i++)
			{
				temp.Printf("%02X ", hdr.frame.frameBuf[i - 1]);
				str << temp;
				if ((i % 20) == 0)
				{
					str << "\r\n";
				}
			}
			RtFrameText->SetLabelText(str);
		}
	}
	int dispTreeNode(wxTreeCtrl* pRtFrameTree, PcapDesNode* Node)
	{
		if (Node)
		{
			spt::String1kB Str;
			Str = Node->Des();
			Str << ":" << Node->FrmDes().c_str();
			if (Node->UsrPri.value.vptr)
			{
				pRtFrameTree->SetItemText(Node->UsrPri.value.vptr, Str.Str());
			}
			if (Node->Child())
			{
				PcapDesNode* now = Node->Child();
				while (now)
				{
					dispTreeNode(pRtFrameTree, now);
					now = now->Next();
				}
			}
		}
		return 0;
	}
	virtual void SaveFile(wxCommandEvent& event)
	{
		wxDateTime date;
		wxFileDialog dia(this, "保存报文", ".", "", "Files (*.cap)|*.cap", wxFD_SAVE);
		if (dia.ShowModal() == wxID_OK)
		{
			pcap_t* ad = pcap_open_dead(1, 65535);
			wxString name = dia.GetFilename();
			pcap_dumper_t* dumpfile = pcap_dump_open(ad, name);
			int32 num = frameArray.size();
			for (int32 i = 0; i < num; i++)
			{
				EthFrameHdr& hdr = frameArray.at(i);
				pcap_dump((u_char*)dumpfile, &hdr.hdr, &hdr.frame.frameBuf[0]);
			}
			pcap_dump_close(dumpfile);
			pcap_close(ad);
		}

		event.Skip(0);
	}
	virtual void PowerUpIniTree()
	{
		IniTree = 0;
		desFile.FreeAllNode();


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

		desFile.SaveXml("GnrFrame");
		String100B str;
		str << ".\\des\\" << "GnrFrame" << ".xml";
		LoadXml(str.Str());
	}
	virtual void LoadXml(wxCommandEvent& event)
	{
		wxGetApp().StopRecv(this);
		BtStart->SetLabelText("开始");
		wxFileDialog dia(this, "打开配置", ".\\des", "", "Files (*.xml)|*.xml", wxFD_OPEN);
		if (dia.ShowModal() == wxID_OK)
		{
			LoadXml(dia.GetPath());
		}
		event.Skip(0);
		ClearFrame(event);
	}
	void LoadXmlNode(PcapDesNode* Node, wxTreeItemId& ParentId)
	{
		if (Node)
		{
			wxTreeItemId Id = RtFrameTree->AppendItem(ParentId, Node->Des());
			Node->UsrPri.value.vptr = Id;
			SptWxTreeItemData* data = new SptWxTreeItemData();
			data->Data().value.vptr = Node;
			SelItem1->Append(Node->Des(), Node);
			SelItem2->Append(Node->Des(), Node);
			RtFrameTree->SetItemData(Id, data);
			PcapDesNode* now = Node->Child();
			while (now)
			{
				LoadXmlNode(now, Id);
				now = now->Next();
			}
		}
	}
	void LoadXml(const char* FileName)
	{
		lastFilterNode1 = 0;
		lastFilterNode2 = 0;
		RtFrameTree->DeleteAllItems();
		RootId = RtFrameTree->AddRoot("Info");
		StampId = RtFrameTree->AppendItem(RootId, "Stamp");
		LenId = RtFrameTree->AppendItem(RootId, "Length");
		desFile.LoadXml(FileName);
		SelItem1->Clear();
		SelItem2->Clear();
		PcapDesNode* root = desFile.Root();
		LoadXmlNode(root, RootId);
		SelItem1->SetSelection(0);
		SelItem2->SetSelection(0);
		IniTree = 1;
		RtFrameTree->ExpandAll();
	}
	virtual void LoadPcap(wxCommandEvent& event) { event.Skip(); }
	virtual void SelNodeChange(wxTreeEvent& event) {
		event.Skip(0);
		wxTreeItemId Id = event.GetOldItem();
		if (Id.GetID())
		{
			SptWxTreeItemData* data = (SptWxTreeItemData*)RtFrameTree->GetItemData(Id);
			if (data)
			{
				PcapDesNode* Node = (PcapDesNode*)data->Data().value.vptr;
				if (Node)
				{
					event.GetOldItem();
					wxTextAttr att = FrameTextAtt;
					RtFrameText->SetStyle(Node->CtxFrom() * 3 + Node->CtxFrom() / 20, Node->CtxEnd() * 3 + Node->CtxEnd() / 20, att);
				}
			}
		}
		Id = event.GetItem();
		if (Id.GetID())
		{
			SptWxTreeItemData* data = (SptWxTreeItemData*)RtFrameTree->GetItemData(Id);
			if (data)
			{
				PcapDesNode* Node = (PcapDesNode*)data->Data().value.vptr;
				if (Node)
				{
					event.GetOldItem();
					wxTextAttr att = FrameTextAtt;
					att.SetBackgroundColour(*wxRED);
					RtFrameText->SetStyle(Node->CtxFrom() * 3 + Node->CtxFrom() / 20, Node->CtxEnd() * 3 + Node->CtxEnd() / 20, att);
				}
			}
		}
	}
	virtual void SelectFilterItem1(wxCommandEvent& event)
	{
		if (lastFilterNode1)
		{
			lastFilterNode1->SetFilter(0, lastFilterNode1->E_Null, "");
		}
		PcapDesNode* node = (PcapDesNode*)event.GetClientData();
		lastFilterNode1 = node;
		event.Skip(0);
		SelItem1->SetClientData(node);
		ChangeFilter(node, SelCdt1->GetSelection(), SelText1->GetLineText(0));
	}
	virtual void SelectFilterCdt1(wxCommandEvent& event)
	{
		PcapDesNode* node = (PcapDesNode*)SelItem1->GetClientData();
		ChangeFilter(node, SelCdt1->GetSelection(), SelText1->GetLineText(0));
		event.Skip(0);
	}
	virtual void SetFilterCtx1(wxCommandEvent& event)
	{
		PcapDesNode* node = (PcapDesNode*)SelItem1->GetClientData();
		ChangeFilter(node, SelCdt1->GetSelection(), SelText1->GetLineText(0));
		event.Skip(0);
	}
	virtual void SelectFilterItem2(wxCommandEvent& event)
	{
		if (lastFilterNode2)
		{
			lastFilterNode2->SetFilter(0, lastFilterNode2->E_Null, "");
		}
		PcapDesNode* node = (PcapDesNode*)event.GetClientData();
		lastFilterNode2 = node;
		SelItem2->SetClientData(node);
		event.Skip(0);
		ChangeFilter(node, SelCdt2->GetSelection(), SelText2->GetLineText(0));
	}
	virtual void SelectFilterCdt2(wxCommandEvent& event)
	{
		PcapDesNode* node = (PcapDesNode*)SelItem2->GetClientData();
		ChangeFilter(node, SelCdt2->GetSelection(), SelText2->GetLineText(0));
		event.Skip(0);
	}
	virtual void SetFilterCtx2(wxCommandEvent& event)
	{
		PcapDesNode* node = (PcapDesNode*)SelItem2->GetClientData();
		ChangeFilter(node, SelCdt2->GetSelection(), SelText2->GetLineText(0));
		event.Skip(0);
	}
	void ChangeFilter(PcapDesNode* node, int Index, const char* Ctx)
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
protected:
	PcapDesNode* lastFilterNode1;
	PcapDesNode* lastFilterNode2;
	wxTreeItemId RootId;
	wxTreeItemId StampId;
	wxTreeItemId LenId;
	wxTextAttr FrameTextAtt;
	virtual void OnTimer(wxTimerEvent& event)
	{
		if (dispRtFrame->Get3StateValue() == wxCHK_CHECKED)
		{
			if (frameArray.size() > 0)
			{
				EthFrameHdr hdr = frameArray.back();
				DispHdrFrame(hdr);
			}
		}
	}
protected:
	bool8 IniTree;
};