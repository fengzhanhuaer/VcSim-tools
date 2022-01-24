
#include"Main.h"
auto GetHexFromAssic = [](uint8* Data, bool8& ok)->uint8
{
	ok = 0;
	uint8 data1;
	if ((*Data <= '9') && (*Data >= '0'))
	{
		data1 = Data[0] - '0';
	}
	else if ((*Data <= 'F') && (*Data >= 'A'))
	{
		data1 = Data[0] - 'A' + 10;
	}
	else
	{
		return 0;
	}
	ok = 1;
	return data1;
};
auto GetData8FromStr = [](uint8* Data, bool8& ok)->uint8
{
	ok = 0;
	uint8 data1, data2;
	data1 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	Data++;
	data2 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	ok = 1;
	data1 = (data1 << 4) + data2;
	return data1;
};
auto GetData16FromStr = [](uint8* Data, bool8& ok)->uint16
{
	ok = 0;
	uint16 data1, data2, data3, data4;
	data1 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	Data++;
	data2 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	Data++;
	data3 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	Data++;
	data4 = GetHexFromAssic(Data, ok);
	if (ok == 0)
	{
		return 0;
	}
	ok = 1;
	data1 = (data1 << 12) + (data2 << 8) + (data3 << 4) + (data4 << 0);
	return data1;
};
bool8 McsLineFmt::Unpack(void* data, uint32 Len)
{
	checkOk = 0;
	if (!data)
	{
		return 0;
	}
	if (Len >= sizeof(rawdata.u8))
	{
		return 0;
	}
	memcpy(rawdata.u8, data, Len);
	fmtdata.mark = rawdata.st.mark;
	bool8 ok;
	fmtdata.len = GetData8FromStr(&rawdata.st.len0, ok);
	if (!ok)
	{
		return 0;
	}
	fmtdata.offset = GetData16FromStr(&rawdata.st.offset0, ok);
	if (!ok)
	{
		return 0;
	}
	fmtdata.type = GetData8FromStr(&rawdata.st.type0, ok);
	if (!ok)
	{
		return 0;
	}
	if (Len != (fmtdata.len * 2 + 11))
	{
		return 0;
	}
	for (uint8 i = 0; i < fmtdata.len; i++)
	{
		fmtdata.ud[i] = GetData8FromStr(&rawdata.st.ud[2 * i], ok);
		if (!ok)
		{
			return 0;
		}
	}
	fmtdata.sum = GetData8FromStr(&rawdata.st.ud[2 * fmtdata.len], ok);
	if (!ok)
	{
		return 0;
	}
	uint8 sum = 0;
	uint8 le = (Len - 3) / 2;
	uint8* p = &fmtdata.len;
	for (uint8 i = 0; i < le; i++)
	{
		sum += p[i];
	}
	sum = (~sum) + 1;
	if (fmtdata.sum != sum)
	{
		return 0;
	}
	return checkOk = 1;
}

bool8 ProgData::Clear()
{
	checkOk = 0;
	prgLen = 0;
	prgSum = 0;
	prgType = 0;
	return 1;
}

InstMainWnd::InstMainWnd()
	:MainWnd(0)
{
	wxCommandEvent event;
	ReFreshNetCard(event);
	adhandle = 0;
}


enum FrameType
{
	FtCmd = 0x0001,
	FtResp,
	FtData,
};
enum CmdType
{
	CtCreateConn = 1,
	CtStartUpdate = 2,
	CtEraseRegion = 4,
	CtReadCheckVal = 8,
	CtPrgData = 0x10,
	CtInitFrmPrm = 0x12,
	CtDataFinishFrm = 20,
	CtOther
};



void InstMainWnd::CheckType(wxCommandEvent& event)
{
	event.Skip(0);
	SendLinkAsk();
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("无响应帧");
		return;
	}
	if ((rframe.ethnetType == 0x88ff) && (rframe.fpgaframeType == 0))
	{
		rframe.unPcapN1();
		if (rframe.frameType == FtResp)
		{
			if (rframe.cmdType == CtCreateConn)
			{
				m_choice1->SetSelection(0);
				rframe.ReadBigEndian(iedType);
				rframe.ReadBigEndian(prgState);
				LogInfo("创建链接成功");
				if (iedType == 0x0001)
				{
					m_textCtrl1->SetLabelText("BPI-N1");
				}
				else if (iedType == 0x0002)
				{
					m_textCtrl1->SetLabelText("DSA-N1");
				}
				else if (iedType == 0x0003)
				{
					m_textCtrl1->SetLabelText("NSA-N1");
				}
				else if (iedType == 0x0004)
				{
					m_textCtrl1->SetLabelText("PMI-N1");
				}
				else if (iedType == 0x0005)
				{
					m_textCtrl1->SetLabelText("BPA-N1");
				}
				else
				{
					m_textCtrl1->SetLabelText("未知");
				}
				wxString str = "IEDType:";
				str += m_textCtrl1->GetLabelText();
				LogInfo(str);
				if (prgState & 0x0001)
				{
					LogInfo("运行状态:" "正常运行");
				}
				else if (prgState & 0x0002)
				{
					LogInfo("运行状态:" "程序更新");
				}
				else
				{
					LogInfo("运行状态:" "未知");
				}
				uint32 sum = 0;
				if (GetCheckSumN1(sum))
				{
					String1000B str;
					str << "当前程序 CRC is ";
					str.FormatHex(sum);
					LogInfo(str.Str());
				}
				else
				{
					LogInfo("获取程序校验码失败");
				}
			}
			else
			{
				LogInfo("命令类型异常");
			}

		}
	}
	else if ((rframe.ethnetType == 0xff88) && (rframe.fpgaframeType == 1))
	{
		//待李华东确定后界面提示装置类型，运行状态
		uint32 iedType, runState;
		rframe.ReadLittleEndian(iedType);
		rframe.ReadLittleEndian(runState);


		SendFrameCmdN2(0xaa33);
		if (!WaitForN2ACK(rframe, 0x5533, 3000))
		{
			LogInfo("校验失败");
			return;
		}
		uint32 bootcrc, appcrc;
		rframe.ReadLittleEndian(bootcrc);
		rframe.ReadLittleEndian(appcrc);
		wxString info = "校验结果正常:";
		info << "BootCrc:" << info.Format("%08X", bootcrc) << " APPCrc:";
		info << info.Format("%08X", appcrc);
		LogInfo(info);
		prgData.checkOk = 1;
		prgData.prgType = m_choice1->GetSelection();
		m_choice1->SetSelection(1);
	}
	else
	{
		LogInfo("帧类型异常");
	}
}

void InstMainWnd::TypeChange(wxCommandEvent& event)
{
	event.Skip(0);
}
#include <wx/textfile.h>
void InstMainWnd::OpenProgram(wxCommandEvent& event)
{
	event.Skip(0);
	if (m_choice1->GetSelection() == 0)
	{
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.mcs)|*.mcs", wxFD_FILE_MUST_EXIST);
		if (dialog.ShowModal() == wxID_OK)
		{
			wxString path = dialog.GetPath();
			int filterIndex = dialog.GetFilterIndex();
			m_textCtrl3->SetLabelText(path);
			m_textCtrl3->SetSelection(path.Len(), path.Len() + 1);
		}
		else
		{
			return;
		}
		prgData.checkOk = 0;
		SalFile file;
		file.SetFullName(dialog.GetPath());
		if (file.OpenReadOnly() == 0)
		{
			LogInfo("打开文件失败");
			return;
		}
		char buf[1000];
		int32 len;
		prgData.prgLen = 0;
		while ((len = file.ReadLine(buf, sizeof(buf))) > 0)
		{
			McsLineFmt fmt;
			fmt.Unpack(buf, len);
			if (fmt.checkOk != 1)
			{
				LogInfo("文件解析异常");
				return;
			}
			if (fmt.fmtdata.type == 0x04)
			{
				prgData.prgFlashStartAddr = fmt.fmtdata.ud[0];
				prgData.prgFlashStartAddr = (prgData.prgFlashStartAddr << 8) | fmt.fmtdata.ud[0];
				prgData.prgFlashStartAddr = (prgData.prgFlashStartAddr << 16);
			}
			else if (fmt.fmtdata.type == 0x00)
			{
				uint32 len = prgData.prgLen + fmt.fmtdata.len;
				if (len < sizeof(prgData.prgData))
				{
					for (uint32 i = 0; i < fmt.fmtdata.len; i++)
					{
						prgData.prgData[prgData.prgLen + i] = fmt.fmtdata.ud[i];
					}
					prgData.prgLen += fmt.fmtdata.len;
				}
				else
				{
					break;
				}
			}
			else if (fmt.fmtdata.type == 0x01)
			{
				prgData.prgSum = 0;
				uint32 add = frmDataMaxLenN1 - prgData.prgLen % frmDataMaxLenN1;
				for (uint32 i = 0; i < add; i++)
				{
					prgData.prgData[prgData.prgLen + i] = 0xff;
				}
				prgData.prgLen += add;
				for (uint32 i = 0; i < prgData.prgLen; i++)
				{
					prgData.prgSum += prgData.prgData[i];
				}
				prgData.checkOk = 1;
				break;
			}
		}
		prgData.prgType = m_choice1->GetSelection();
		String1000B str;
		str << "文件信息:";
		str << "CheckOk-" << prgData.checkOk;
		str << " PrgLen-" << prgData.prgLen;
		str << " PrgCrc-"; str.FormatHex(prgData.prgSum);
		LogInfo(str.Str());
	}
	else if (m_choice1->GetSelection() == 1)
	{
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.bin)|*.bin", wxFD_FILE_MUST_EXIST);
		wxString path;
		if (dialog.ShowModal() == wxID_OK)
		{
			path = dialog.GetPath();
			int filterIndex = dialog.GetFilterIndex();
			m_textCtrl3->SetLabelText(path);
			m_textCtrl3->SetSelection(path.Len(), path.Len() + 1);
		}
		else
		{
			return;
		}
		prgData.checkOk = 0;
		FILE* file = fopen(path, "rb");
		if (file)
		{

		}
		else
		{
			LogInfo("打开文件失败\n");
			return;
		}

		struct _stat statbuf;
		_stat(path, &statbuf);

		unsigned int totalSize = statbuf.st_size;
		if ((totalSize) <= (32))
		{
			LogInfo("文件过小\n");
			fclose(file);
			return;
		}
		if (totalSize > sizeof(prgData.prgData))
		{
			LogInfo("文件过大\n");
			fclose(file);
			return;
		}
		prgData.checkOk = 0;
		memset(prgData.prgData, 0x0, totalSize);
		unsigned int header[8] = { 0 };
		unsigned int filesize = statbuf.st_size - sizeof(header);
		fread(header, 1, sizeof(header), file);
		fread(prgData.prgData, 1, filesize, file);
		fclose(file);
		unsigned int sum = 0;
		for (unsigned int i = 0; i < filesize; i++)
		{
			sum += prgData.prgData[i];
		}
		bool8 ok = 1;
		if (header[0] != filesize)
		{
			wxString info = "校验异常:";
			info << "Size:" << header[0] << "!=" << filesize << "\n";;
			LogInfo(info);
			ok = 0;
		}
		if (header[1] != sum)
		{
			wxString info = "校验异常:";
			info << "Crc:" << header[1] << "!=" << sum << "\n";;
			LogInfo(info);
			ok = 0;
		}
		if (ok)
		{
			wxString info = "文件校验正常:";
			info << "Size:" << filesize << " Crc:";
			info << info.Format("%08X", sum) << "\n";
			LogInfo(info);
			prgData.checkOk = 1;
			prgData.prgLen = filesize;
			prgData.prgSum = sum;
			prgData.prgType = m_choice1->GetSelection();
		}
	}
}
void InstMainWnd::NetCardChange(wxCommandEvent& event)
{
	adhandle = 0;
	event.Skip(0);
}
void InstMainWnd::ReFreshNetCard(wxCommandEvent& event)
{
	adhandle = 0;
	event.Skip(0);
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	char infobuf[PCAP_ERRBUF_SIZE + 1];
	pcap_if_t* alladdevs;
	pcap_if_t* curaddev;
	wxChoice* m_choice = m_choice2;
	if (m_choice->GetCount() > 0)
	{
		alladdevs = (pcap_if_t*)m_choice->GetClientData();
		if (alladdevs)
		{
			pcap_freealldevs(alladdevs);
		}
	}
	/* Retrieve the device list */
	if (pcap_findalldevs(&alladdevs, errbuf) == -1)
	{
		snprintf(infobuf, sizeof(infobuf), "Error: %s", errbuf);
		LogInfo(infobuf);
	}
	m_choice->Clear();
	/* Scan the list printing every entry */
	pcap_if_t* d;
	int i = 0;
	m_choice->SetClientData(alladdevs);
	for (d = alladdevs; d; d = d->next)
	{
		m_choice->Insert(d->description, i);
		i++;
	}
	if (alladdevs)
	{
		curaddev = alladdevs;
		m_choice->SetSelection(0);
	}
}

void InstMainWnd::StartUpdate(wxCommandEvent& event)
{
	if (isUpdating)
	{
		LogInfo("升级中，请稍候再试");
		return;
	}
	if (prgData.prgType != m_choice1->GetSelection())
	{
		LogInfo("打开的程序类型与装置类型不符");
		return;
	}
	if (prgData.checkOk == 0)
	{
		LogInfo("程序校验异常,请重新开发或检查程序文件");
		return;
	}
	if (prgData.prgType == 0)
	{
		FpgaN1Update();
	}
	else if (prgData.prgType == 1)
	{
		LogInfo("该类型装置升级暂未实现");
		return;
	}
}

pcap_t* InstMainWnd::OpenAdHandle()
{
	adhandle = 0;
	wxChoice* m_choice = m_choice2;
	pcap_if_t* dif = 0;
	int todev = m_choice->GetCount();
	if (todev > 0)
	{
		dif = (pcap_if_t*)m_choice->GetClientData();
		if (!dif)
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
	int sec = m_choice->GetSelection();
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
		return 0;
	}
	if (d == 0)
	{
		return 0;
	}
	char errbuf[PCAP_ERRBUF_SIZE + 1];
	char infobuf[PCAP_ERRBUF_SIZE + 1];
	if ((adhandle = pcap_open_live(d->name, 65536, 0, 1, errbuf)) == 0)
	{
		snprintf(infobuf, sizeof(infobuf), "Error: %s", errbuf);
		LogInfo(infobuf);
	}
	else
	{
		snprintf(infobuf, sizeof(infobuf), "Open: %s", d->description);
		LogInfo(infobuf);
	}
	return adhandle;
}

void InstMainWnd::LogInfo(const char* Info)
{
	wxDateTime date;
	date = date.Now();
	m_textCtrl4->AppendText(date.FormatTime() << " ");
	m_textCtrl4->AppendText(Info);
	m_textCtrl4->AppendText("\n");
}

void InstMainWnd::ClearAd()
{
	pcap_pkthdr* hdr;
	const u_char* p;
	pcap_next_ex(adhandle, &hdr, &p);
	while (pcap_next_ex(adhandle, &hdr, &p) > 0)
	{

	}
}
void InstMainWnd::SendLinkAsk()
{
	if (adhandle == 0)
	{
		if (OpenAdHandle() == 0)
		{
			LogInfo("网卡设备打开失败");
			return;
		}
	}
	SendFrameCmdN1(CtCreateConn);
	SendFrameCmdN2(0xaa00);
}

bool8 InstMainWnd::AskForUpdateN1()
{
	SendFrameCmdN1(CtStartUpdate);
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("无响应帧");
		return 0;
	}
	if (rframe.ethnetType != 0x88ff)
	{
		LogInfo("帧类型异常");
		return 0;
	}
	rframe.unPcapN1();
	if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtStartUpdate))
	{
		return 0;
	}
	return 1;
}
void InstMainWnd::SendFrameCmdN1(uint16 Cmd)
{
	SendFrame frame;
	frame.WriteBigEndian((uint16)0x88ff);
	frame.WriteBigEndian((uint16)0x0028);
	frame.WriteBigEndian((uint16)0x0003);
	frame.WriteBigEndian((uint32)0x00000000);
	frame.WriteBigEndian((uint16)0x6868);
	frame.WriteBigEndian((uint16)0x0010);
	frame.WriteBigEndian((uint16)0x5858);
	frame.WriteBigEndian((uint16)FtCmd);
	frame.WriteBigEndian((uint16)0x0000);
	frame.WriteBigEndian((uint16)0x0000);
	frame.WriteBigEndian((uint16)0x0000);
	frame.WriteBigEndian((uint16)Cmd);
	frame.WriteBigEndian((uint32)0x00000000);
	frame.WriteBigEndian((uint32)0x00000000);
	frame.WriteBigEndian((uint32)0x00000000);
	frame.AddSum();
	frame.WriteBigEndian((uint16)0x1616);
	ClearAd();
	frame.SendBy(adhandle);
	return;
}
void InstMainWnd::SendFrameCmdN2(uint16 Cmd)
{
	SendN2Frame frame;
	frame.Write((uint16)Cmd);
	frame.Write((uint16)0x0000);
	frame.Write((uint16)0x0000);
	frame.Write((uint16)0x0000);
	frame.Write((uint16)0x0000);
	ClearAd();
	frame.SendBy(adhandle);
	return;
}
bool8 InstMainWnd::SendDataAndWaitRspN1(uint32 FrmTotal, uint32 FrmNo, uint32 FrmOffSet, uint32 FrmLen)
{
	SendFrame frame;
	frame.WriteBigEndian((uint16)0x88ff);
	frame.WriteBigEndian((uint16)0x0418);
	frame.WriteBigEndian((uint16)0x0003);
	frame.WriteBigEndian((uint32)0x00000000);
	frame.WriteBigEndian((uint16)0x6868);
	frame.WriteBigEndian((uint16)0x0400);
	frame.WriteBigEndian((uint16)0x5858);
	frame.WriteBigEndian((uint16)FtData);
	frame.WriteBigEndian((uint16)FrmNo);
	frame.WriteBigEndian((uint16)FrmTotal);
	uint32 sum = 0;
	for (uint32 i = 0; i < FrmLen; i++)
	{
		frame.Write(&prgData.prgData[i + FrmOffSet], 1);
		sum += prgData.prgData[i + FrmOffSet];
	}
	frame.AddSum();
	frame.WriteBigEndian((uint16)0x1616);
	ClearAd();
	int32 res = frame.SendBy(adhandle);
	if (res < 0)
	{
		LogInfo("数据帧发送失败");
		return 0;
	}
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("无数据响应帧");
		return 0;
	}
	if (rframe.ethnetType != 0x88ff)
	{
		LogInfo("帧类型异常");
		return 0;
	}
	rframe.unPcapN1();
	if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtPrgData))
	{
		return 0;
	}
	uint32 cmdres = 0;
	rframe.ReadBigEndian(cmdres);

	return 1;
}
bool8 InstMainWnd::GetCheckSumN1(uint32& Sum)
{
	SendFrameCmdN1(CtReadCheckVal);
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("无数据响应帧");
		return 0;
	}
	if (rframe.ethnetType != 0x88ff)
	{
		LogInfo("帧类型异常");
		return 0;
	}
	rframe.unPcapN1();
	if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtReadCheckVal))
	{
		return 0;
	}
	rframe.ReadBigEndian(Sum);
	return 1;
}
void InstMainWnd::FpgaN1Update()
{
	SendLinkAsk();
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("创建链接失败");
		return;
	}
	if (rframe.fpgaframeType != 0)
	{
		LogInfo("创建链接FPGA类型异常");
		return;
	}
	rframe.unPcapN1();
	if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtCreateConn))
	{
		LogInfo("创建链接响应帧异常");
		return;
	}
	LogInfo("创建链接成功");
	if (AskForUpdateN1())
	{
		wxString str = "程序升级设置成功，请重启装置";
		wxMessageDialog dia(this, str, "", wxOK | wxCENTRE);
		dia.ShowModal();
		LogInfo(str);
	}
	else
	{
		LogInfo("升级命令响应失败");
	}
	wxMessageDialog dia(this, "是否重启完成?", "", wxYES_NO | wxCANCEL | wxCENTRE);
	while (1)
	{
		int res = dia.ShowModal();
		if (res == wxID_YES)
		{
			LogInfo("重启完成，进行升级");
			break;
		}
		else if (res == wxID_NO)
		{
			LogInfo("未重启完成，继续等待");
			continue;
		}
		else if (res == wxID_CANCEL)
		{
			LogInfo("取消继续升级");
			return;
		}
	}
	SendLinkAsk();

	SendFrameCmdN1(CtInitFrmPrm);
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("初始化通讯帧失败");
		return;
	}
	rframe.unPcapN1();
	if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtInitFrmPrm))
	{
		LogInfo("初始化通讯响应帧异常");
		return;
	}
	static auto callback = [](void* ptr)
	{
		InstMainWnd& wnd = *(InstMainWnd*)ptr;
		wnd.isUpdating = 1;
		uint32 total = (wnd.prgData.prgLen + frmDataMaxLenN1 - 1) / frmDataMaxLenN1;
		uint32 frmNo = 0;
		uint32 offset = 0;
		while (frmNo < total)
		{
			if (wnd.SendDataAndWaitRspN1(total, frmNo, offset, frmDataMaxLenN1))
			{
				String1000B str;
				str << "升级中:" << frmNo << "/" << total;
				wnd.m_button3->SetLabel(str.Str());
				frmNo++;
				offset += frmDataMaxLenN1;
			}
			else
			{
				wnd.m_button3->SetLabel("开始");
				String1000B str;
				str = "数据帧响应失败";
				str << total << " " << frmNo;
				wnd.LogInfo(str.Str());
				wnd.isUpdating = 0;
				return;
			}
		}
		wnd.m_button3->SetLabel("开始");
		wnd.SendFrameCmdN1(CtDataFinishFrm);
		RecvFrame rframe;
		rframe.RecvFrom(wnd.adhandle, 1000);
		rframe.unPcap();
		if (rframe.frmOk == 0)
		{
			wnd.LogInfo("升级结束帧接收异常");
			wnd.isUpdating = 0;
			return;
		}
		rframe.unPcapN1();
		if ((rframe.ethnetType != 0x88ff) || (rframe.frameType != FtResp) || (rframe.cmdType != CtDataFinishFrm))
		{
			wnd.LogInfo("升级结束响应帧异常");
			wnd.isUpdating = 0;
			return;
		}
		String1000B str;
		str = "升级完成，请重启装置后检查校验码";
		wnd.LogInfo(str.Str());
		wnd.isUpdating = 0;
		return;
	};
	Thread* th = new Thread(callback, this);
	th->Create();
	th->SetPriority(WXTHREAD_MAX_PRIORITY - 1);
	th->Run();
}
void InstMainWnd::FpgaN2Update()
{
	SendLinkAsk();
	RecvFrame rframe;
	rframe.RecvFrom(adhandle, 1000);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("创建链接失败");
		return;
	}
	if (rframe.fpgaframeType != 1)
	{
		LogInfo("创建链接FPGA类型异常");
		return;
	}
	rframe.unPcapN2();
	if ((rframe.ethnetType != 0xff88) || (rframe.cmdType != 0x5500))
	{
		LogInfo("创建链接响应帧异常");
		return;
	}
	LogInfo("创建链接成功");
	SendFrameCmdN2(0xaa11);
	if (!WaitForN2ACK(rframe, 0x5511, 3000))
	{
		LogInfo("擦除失败");
		return;
	}
	LogInfo("擦除成功");
	uint16 frmLen = 512;
	uint16 frameTotal = (prgData.prgLen + frmLen - 1) / frmLen;
	uint16 frameNo = 0;
	uint16 frameLen = 0;
	uint16 retry = 0;
	while (frameNo < frameTotal)
	{
		if ((frameNo + 1) >= frameTotal)
		{
			frameLen = prgData.prgLen - frmLen * frameNo;
		}
		else
		{
			frameLen = frmLen;
		}
		SendN2Frame frame;
		frame.Write((uint16)0xaa22);
		frame.Write((uint16)frameTotal);
		frame.Write((uint16)frameNo);
		frame.Write((uint16)frameLen);
		frame.Write(prgData.prgData + frmLen * frameNo, frameLen);
		ClearAd();
		frame.SendBy(adhandle);
		frameNo++;
		if (!WaitForN2ACK(rframe, 0x5522, 200))
		{
			retry++;
			if (retry > 3)
			{
				wxString str;
				str = "数据帧响应失败";
				str << frameTotal << " " << frameNo;
				LogInfo(str);
				return;
			}
			continue;
		}
		wxString str;
		str << "升级中:";
		str << frameTotal << " " << frameNo;
		LogInfo(str);
	}
	LogInfo("程序写入完成");
	SendFrameCmdN2(0xaa33);
	if (!WaitForN2ACK(rframe, 0x5533, 3000))
	{
		LogInfo("校验帧接收失败");
		return;
	}
	uint32 bootcrc, appcrc;
	rframe.ReadLittleEndian(bootcrc);
	rframe.ReadLittleEndian(appcrc);
	if (appcrc == prgData.prgSum)
	{
		wxString info = "校验结果正常:";
		info << "BootCrc:" << info.Format("%08X", bootcrc) << " APPCrc:";
		info << info.Format("%08X", appcrc);
		LogInfo(info);
	}
	else
	{
		wxString info = "校验结果异常:";
		info << "BootCrc:" << info.Format("%08X", bootcrc);
		info << " APPCrc:" << info.Format("%08X", appcrc);
		info << " File:" << info.Format("%08X", prgData.prgSum);
		LogInfo(info);
	}
}
bool8 InstMainWnd::WaitForN2ACK(RecvFrame& rframe, uint16 Cmd, uint32 Ms)
{
	rframe.RecvFrom(adhandle, Ms);
	rframe.unPcap();
	if (rframe.frmOk == 0)
	{
		LogInfo("帧接收异常");
		return 0;
	}
	if (rframe.fpgaframeType != 1)
	{
		LogInfo("FPGA类型异常");
		return 0;
	}
	rframe.unPcapN2();
	if ((rframe.ethnetType != 0xff88))
	{
		LogInfo("帧类型异常");
		return 0;
	}
	if ((rframe.cmdType != Cmd))
	{
		LogInfo("帧类型异常");
		return 0;
	}
	return 1;
}