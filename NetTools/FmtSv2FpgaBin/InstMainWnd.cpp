#include"pcap.h"
#include"ApiProject.h"
#include"Main.h"

using namespace spt;
InstMainWnd::InstMainWnd()
	:MainWnd(0)
{
}

struct SvFrame
{
	int32 unpackFrame(const uint8* EhnetPcak)
	{
		uint16 type;
		uint16 offset;
		if ((EhnetPcak[12] == 0x81) && (EhnetPcak[13] == 0x00))
		{
			offset = 16;
		}
		else
		{
			offset = 12;
		}
		frameok = 0;
		ChangeEndian(&type, (void*)&EhnetPcak[offset], sizeof(type));
		if (type != 0x88ba)
		{
			return -1;
		}
		offset += 2;
		ChangeEndian(&appid, (void*)&EhnetPcak[offset], sizeof(appid));
		offset += 2;
		ChangeEndian(&appLen, (void*)&EhnetPcak[offset], sizeof(appLen));
		offset += 2;
		offset += 2;
		offset += 2;
		if (EhnetPcak[offset] == 0x60)
		{
			offset += 1;
			if (EhnetPcak[offset] < 0x80)
			{
				pduLen = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x81)
			{
				offset += 1;
				pduLen = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x82)
			{
				offset += 1;
				ChangeEndian(&pduLen, (void*)&EhnetPcak[offset], sizeof(appLen));
				offset += 2;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}

		if (EhnetPcak[offset] == 0x80)
		{
			offset += 1;
			if (EhnetPcak[offset] == 0x01)
			{
				offset += 1;
				asduNum = EhnetPcak[offset];
				offset += 1;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}

		if (EhnetPcak[offset] == 0xa2)
		{
			offset += 1;
			if (EhnetPcak[offset] < 0x80)
			{
				sizeAsdu = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x81)
			{
				offset += 1;
				sizeAsdu = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x82)
			{
				offset += 1;
				ChangeEndian(&sizeAsdu, (void*)&EhnetPcak[offset], sizeof(appLen));
				offset += 2;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x30)
		{
			offset += 1;
			if (EhnetPcak[offset] < 0x80)
			{
				asdu1Len = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x81)
			{
				offset += 1;
				asdu1Len = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x82)
			{
				offset += 1;
				ChangeEndian(&asdu1Len, (void*)&EhnetPcak[offset], sizeof(appLen));
				offset += 2;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x80)
		{
			offset += 1;
			if (EhnetPcak[offset] < 0x80)
			{
				svIdLen = EhnetPcak[offset];
				offset += 1;
				svId.Clear();
				char buf[200];
				memcpy(buf, &EhnetPcak[offset], svIdLen);
				buf[svIdLen] = 0;
				offset += svIdLen;
				svId = buf;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x82)
		{
			offset += 1;
			if (EhnetPcak[offset] == 0x02)
			{
				offset += 1;
				ChangeEndian(&sampCount, (void*)&EhnetPcak[offset], sizeof(sampCount));
				offset += 2;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x83)
		{
			offset += 1;
			if (EhnetPcak[offset] == 0x04)
			{
				offset += 1;
				ChangeEndian(&cfgVer, (void*)&EhnetPcak[offset], sizeof(cfgVer));
				offset += 4;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x85)
		{
			offset += 1;
			if (EhnetPcak[offset] == 0x01)
			{
				offset += 1;

				offset += 1;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		if (EhnetPcak[offset] == 0x87)
		{
			offset += 1;
			if (EhnetPcak[offset] < 0x80)
			{
				sizeOfData = EhnetPcak[offset];
				offset += 1;
			}
			else if (EhnetPcak[offset] == 0x81)
			{
				offset += 1;
				sizeOfData = EhnetPcak[offset];
				offset += 1;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
		int32 endloop = sizeOfData / 8;
		if (endloop > M_ArrLen(cell))
		{
			endloop = M_ArrLen(cell);
		}
		for (int32 i = 0; i < endloop; i++)
		{
			ChangeEndian(&cell[i].v, (void*)&EhnetPcak[offset], 4);
			offset += 4;
			ChangeEndian(&cell[i].q, (void*)&EhnetPcak[offset], 4);
			offset += 4;
		}
		frameok = 1;
		return 0;
	}
	bool8 frameok;
	uint16 appid;
	uint16 appLen;
	uint16 pduLen;
	uint16 asduNum;
	uint16 sizeAsdu;
	uint16 asdu1Len;
	uint16 svIdLen;
	String200B svId;
	uint16 sampCount;
	uint32 cfgVer;
	uint32 sizeOfData;
	struct svCell
	{
		int32 v;
		uint32 q;
	}cell[100];
};

struct SvFrameSequence
{
	SvFrame templateFrame;
	uint32 frameNum;
	SvFrame svFrame[1000000];
};
uint32 GetEthnetType(const uint8* EhnetPcak)
{
	if (!EhnetPcak)
	{
		return -1;
	}
	uint16 type;
	uint16 offset;
	if ((EhnetPcak[12] == 0x81) && (EhnetPcak[13] == 0x00))
	{
		offset = 16;
	}
	else
	{
		offset = 12;
	}
	ChangeEndian(&type, (void*)&EhnetPcak[offset], sizeof(type));
	return type;
}
#include "wx/busyinfo.h"
void InstMainWnd::FmtSv2FpgaBin(wxCommandEvent& event)
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
	{

		wxBusyInfo wait("打开成功,转换中", this);
		while ((res = pcap_next_ex(fp, &header, &pkt_data)) >= 0)
		{
			psvs->templateFrame.unpackFrame(pkt_data);
			if (psvs->templateFrame.frameok == 1)
			{
				psvs->svFrame[0].unpackFrame(pkt_data);
				psvs->frameNum = 1;
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
				break;
			}
		}
		wxString path;
		path = dia.GetPath();
		path.Replace(".", "_");
		CreateDirectory(path.c_str(), 0);
		uint32 endloop = psvs->templateFrame.sizeOfData / 8;
		for (uint32 i = 0; i < endloop; i++)
		{
			String200B str;
			str = path.c_str();
			str << "\\";
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
	wxMessageBox("转换完成");
}

