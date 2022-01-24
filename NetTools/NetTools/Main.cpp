#include "pcap-int.h"
#include "Main.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
	FilePath path;
	path.Set(".\\des");
	path.Creat();

	packRecvThread = 0;
	RecvDriverFirst = 0;
	adhandle = 0;
	if (!wxApp::OnInit())
		return false;
	Inst = new MainWndInst();
	Inst->Show();
	return true;
}

bool MainApp::OpenNetCard(pcap_if_t* netDev)
{
	pcap_if_t* dev = netDev;
	if (!dev)
	{
		enableRecv = 0;
		MsSleep(100);
		if (adhandle)
		{
			pcap_close(adhandle);
		}
		adhandle = 0;
		return 0;
	}
	strcpy(pcap_if_t_name, dev->name);
	char errbuf[PCAP_ERRBUF_SIZE];
	char infobuf[PCAP_ERRBUF_SIZE + 1];
	if ((adhandle = pcap_open_live(pcap_if_t_name, 65536, 1, 50, errbuf)) == 0)
	{
		snprintf(infobuf, sizeof(infobuf), "Error: %s\n", errbuf);
		Inst->SetInfo(infobuf);
	}
	else
	{
		snprintf(infobuf, sizeof(infobuf), "Open: %s\n", dev->description);
		Inst->SetInfo(infobuf);
	}
	if (packRecvThread)
	{

	}
	else
	{
		auto callback = [](void*) {
			wxGetApp().StartRecv();
		};
		packRecvThread = new Thread(callback, 0);
		packRecvThread->Create();
		packRecvThread->SetPriority(WXTHREAD_DEFAULT_PRIORITY + 20);
		packRecvThread->Run();
	}
	enableRecv = 1;
	return 1;
}

bool MainApp::CloseNetCard()
{
	if (enableRecv)
	{
		enableRecv = 0;
		MsSleep(100);
		if (adhandle)
		{
			pcap_close(adhandle);
		}
		adhandle = 0;
		return 1;
	}
	return 0;
}

bool MainApp::StartRecv(class RecvDriver* Driver)
{
	if (Driver)
	{
		Driver->enRecv = 0;
		if (RecvDriverFirst)
		{
			class RecvDriver* now = RecvDriverFirst;
			while (now && now->next)
			{
				if (now == Driver)
				{
					Driver->enRecv = 1;
					return 1;
				}
				now = now->next;
			}
			now->next = Driver;
			Driver->next = 0;
		}
		else
		{
			RecvDriverFirst = Driver;
		}
		Driver->enRecv = 1;
		return 1;
	}
	return 0;
}
bool MainApp::StopRecv(RecvDriver* Driver)
{
	Driver->enRecv = 0;
	return 1;
}
bool MainApp::StopRecv()
{
	enableRecv = 0;
	if (adhandle)
	{
		pcap_close(adhandle);
		adhandle = 0;
		if (RecvDriverFirst)
		{
			class RecvDriver* now = RecvDriverFirst;
			while (now)
			{
				now->enRecv = 0;
				now = now->next;
			}
		}
	}
	return false;
}
void MainApp::Packet_Recv_Handler(MainApp* app, const pcap_pkthdr* header, const u_char* pkt_data)
{
	if (enableRecv == 0)
	{
		return;
	}
	if (app != this)
	{
		return;
	}
	if (RecvDriverFirst)
	{
		class RecvDriver* now = RecvDriverFirst;
		while (now)
		{
			if (now->enRecv)
			{
				now->Packet_Recv_Handler(now, header, pkt_data);
			}
			now = now->next;
		}
	}
}

bool MainApp::StartRecv()
{
	struct pcap_pkthdr* header;
	const u_char* pkt_data;
	while (1)
	{
		if (enableRecv && adhandle)
		{
			if (pcap_next_ex(adhandle, &header, &pkt_data) > 0)
			{
				wxGetApp().Packet_Recv_Handler((MainApp*)this, header, pkt_data);
			}
		}
		else if (packRecvThread)
		{
			packRecvThread->Sleep(100);
		}
		else
		{
			MsSleep(100);
		}
	}
	return 1;
}

void MainWndInst::OpenSvPcap2Bin(wxCommandEvent& event)
{
	event.Skip(0);
	wxFileDialog dia(this, "打开报文", ".\\", "", "Files ( *.pcap)|*.pcap|Files( *.cap)|*.cap", wxFD_OPEN);
	if (dia.ShowModal() != wxID_OK)
	{
		return;
	}
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* fp = pcap_open_offline(dia.GetPath(), errbuf);
	if (!fp)
	{
		return;
	}
	int res;
	struct pcap_pkthdr* header;
	const u_char* pkt_data;
	SvFrameSequence* psvs = new SvFrameSequence;
	if (!psvs)
	{
		return;
	}
	psvs->frameNum = 0;
	while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
	{
		psvs->templateFrame.unpackFrame(pkt_data);
		if (psvs->templateFrame.frameok == 1)
		{
			psvs->svFrame[0].unpackFrame(pkt_data);
			psvs->frameNum = 1;
			break;
		}
	}
	while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
	{
		psvs->svFrame[psvs->frameNum].unpackFrame(pkt_data);
		if ((psvs->svFrame[psvs->frameNum].frameok == 1) && (psvs->svFrame[psvs->frameNum].appid == psvs->templateFrame.appid))
		{
			psvs->frameNum++;
			if (psvs->frameNum >= M_ArrLen(psvs->svFrame))
			{
				break;
			}
		}
	}
	String200B str;
	str = ".\\out";
	MkDir(str.Str());
	uint32 endloop = psvs->templateFrame.sizeOfData / 8;
	for (uint32 i = 0; i < endloop; i++)
	{
		String200B str;
		str = ".\\out\\";
		str << dia.GetFilename() << i << ".txt";
		FILE* f = fopen(str.Str(), "w");
		if (!f)
		{
			break;
		}
		for (uint32 j = 0; j < psvs->frameNum; j++)
		{
			String200B str;
			str.FormatBin((uint32)psvs->svFrame[j].cell[i].v) << "\n";
			fwrite(str.Str(), str.StrLen(), 1, f);
		}
		fclose(f);
	}
	delete psvs;
}

void MainWndInst::SendEthnetFrame(wxCommandEvent& event)
{
	sendEthFrame = 0;
	event.Skip(0);
	auto callback = [](void* para)
	{
		MainWndInst* wnd = (MainWndInst*)para;
		pcap_t* adhandle;
		char pcap_if_t_name[512];
		pcap_if_t* dev = wnd->GetCurNetCard();
		if (!dev)
		{
			return;
		}
		strcpy(pcap_if_t_name, dev->name);
		char errbuf[PCAP_ERRBUF_SIZE];
		char infobuf[PCAP_ERRBUF_SIZE + 1];
		if ((adhandle = pcap_open_live(pcap_if_t_name, 65536, 1, 1000, errbuf)) == 0)
		{
			snprintf(infobuf, sizeof(infobuf), "Error: %s\n", errbuf);
		}
		else
		{
			snprintf(infobuf, sizeof(infobuf), "Open: %s\n", dev->description);
		}
		wnd->SetInfo(infobuf);

		if (!adhandle)
		{
			return;
		}
		wnd->sendEthFrame = 1;

		unsigned char buf[3200];
		String5000B str;
		str = wnd->m_textCtrl4->GetValue().c_str();
		uint32 loopend = str.StrLen();
		TransString ts;
		ts.SetBuf(str.Str());
		uint32 framelen;
		for (framelen = 0; framelen < loopend; framelen++)
		{
			buf[framelen] = ts.GetHex(0, 2);
			if (ts.IsEnd())
			{
				break;
			}
		}
		uint32 sendnum = (uint32)wnd->m_spinCtrl3->GetValue();
		uint32 lastsendstamp = HwUsCnt();
		uint32 period = (wnd->m_spinCtrlDouble1->GetValue() * 1000);
		PacketSetNumWrites(adhandle->adapter, 1);
		for (uint32 i = 0; i < sendnum; i++)
		{
			if (!wnd->sendEthFrame)
			{
				break;
			}
			pcap_sendpacket(adhandle, buf, framelen);
			do
			{
				uint32 now = HwUsCnt();
				uint32 delta = lastsendstamp - now;
				if (delta >= period)
				{
					lastsendstamp = now;
					break;
				}
			} while (1);
		}
		pcap_close(adhandle);
	};
	Thread* th = new Thread(callback, (void*)this);
	th->Create();
	th->SetPriority(WXTHREAD_MAX_PRIORITY);
	th->Run();
}
