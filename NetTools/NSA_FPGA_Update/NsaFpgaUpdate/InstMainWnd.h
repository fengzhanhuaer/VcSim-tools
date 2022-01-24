#pragma once
#include"FpgaUpdate.h"

struct McsLineFmt
{
	union data
	{
		uint8 u8[200];
		struct Fmt
		{
			uint8 mark;
			uint8 len0;
			uint8 len1;
			uint8 offset0;
			uint8 offset1;
			uint8 offset2;
			uint8 offset3;
			uint8 type0;
			uint8 type1;
			uint8 ud[150];
		}st;
	}rawdata;
	struct fmtData
	{
		uint8 mark;
		uint8 len;
		uint16 offset;
		uint8 type;
		uint8 ud[150];
		uint8 sum;
	}fmtdata;
	bool8 checkOk;
	bool8 Unpack(void* data, uint32 Len);
};

struct ProgData
{
	bool8 checkOk;
	uint32 prgType;
	uint32 prgLen;
	uint32 prgSum;
	uint32 prgFlashStartAddr;
	uint8 prgData[10 * 10234 * 1024];
	bool8 Clear();
};
const uint8 UpdateFrameDstMac[] = { 0x01,0x0C , 0xCD , 0x04 , 0xBB ,0x01 };
const uint8 UpdateFrameN2DstMac[] = { 0x01,0x0C , 0xCD , 0x05 , 0xDD ,0x01 };
const uint8 UpdateFrameSurMac[] = { 0x01,0x0C , 0xCD , 0x04 , 0xAA ,0x01 };
const uint8 UpdateFrameN2SurMac[] = { 0x01,0x0C , 0xCD , 0x05 , 0xCC ,0x01 };
const uint8 UpdateFrameVlan[] = { 0x81,0x00,0x00,0x00 };
const uint32 frmDataMaxLenN1 = 1024;
struct SendFrame
{
	uint16 writer;
	uint8 frame[1600];

	SendFrame()
	{
		Clear();
		Write(UpdateFrameDstMac, sizeof(UpdateFrameDstMac));
		Write(UpdateFrameSurMac, sizeof(UpdateFrameSurMac));
		Write(UpdateFrameVlan, sizeof(UpdateFrameVlan));
	}
	int32 Write(const void* Sur, int32 size)
	{
		memcpy(frame + writer, Sur, size);
		writer += size;
		return size;
	}
	int32 WriteBigEndian(uint32 data)
	{
		uint8* p = (uint8*)&data;
		frame[writer + 0] = p[3];
		frame[writer + 1] = p[2];
		frame[writer + 2] = p[1];
		frame[writer + 3] = p[0];
		writer += sizeof(data);
		return sizeof(data);
	}
	int32 WriteBigEndian(uint16 data)
	{
		uint8* p = (uint8*)&data;
		frame[writer + 0] = p[1];
		frame[writer + 1] = p[0];
		writer += sizeof(data);
		return sizeof(data);
	}
	int32 SendBy(pcap_t* adhandle)
	{
		return pcap_sendpacket(adhandle, frame, writer);
	}
	void AddSum()
	{
		uint32 s = 0;
		for (uint32 i = 0x1e; i < writer; i++)
		{
			s += frame[i];
		}
		WriteBigEndian(s);
	}
	void Clear() { writer = 0; }
};
struct SendN2Frame
{
	uint16 writer;
	uint8 frame[1600];

	SendN2Frame()
	{
		Clear();
		Write(UpdateFrameN2DstMac, sizeof(UpdateFrameN2DstMac));
		Write(UpdateFrameN2SurMac, sizeof(UpdateFrameN2SurMac));
		uint16 data = 0xff88;
		Write(UpdateFrameVlan, sizeof(UpdateFrameVlan));
		data = 0;
		Write(UpdateFrameVlan, sizeof(UpdateFrameVlan));
		data = 0;
		Write(UpdateFrameVlan, sizeof(UpdateFrameVlan));
		data = 0;
		Write(UpdateFrameVlan, sizeof(UpdateFrameVlan));
	}
	int32 Write(const void* Sur, int32 size)
	{
		memcpy(frame + writer, Sur, size);
		writer += size;
		return size;
	}
	int32 Write(uint32 data)
	{
		uint8* p = (uint8*)&data;
		frame[writer + 0] = p[0];
		frame[writer + 1] = p[1];
		frame[writer + 2] = p[2];
		frame[writer + 3] = p[3];
		writer += sizeof(data);
		return sizeof(data);
	}
	int32 Write(uint16 data)
	{
		uint8* p = (uint8*)&data;
		frame[writer + 0] = p[0];
		frame[writer + 1] = p[1];
		writer += sizeof(data);
		return sizeof(data);
	}
	int32 SendBy(pcap_t* adhandle)
	{
		AddSum();
		return pcap_sendpacket(adhandle, frame, writer);
	}
	void AddSum()
	{
		uint16 s = 0;
		uint16 len = writer - 20 + 2;
		frame[14] = len;
		frame[15] = len >> 8;
		for (uint32 i = 20; i < writer; i++)
		{
			s += frame[i];
		}
		Write(s);
	}
	void Clear() { writer = 0; }
};
struct RecvFrame
{
	uint16 reader;
	uint16 writer;
	uint8 frame[1600];
	RecvFrame()
	{
		writer = reader = 0;
	}
	uint16 RecvFrom(pcap_t* adhandle, uint32 Ms)
	{

		Clear();
		pcap_pkthdr* hdr;
		const u_char* p = 0;
		uint32 us = HwUsCnt();
		Ms *= 1000;
		while (1)
		{
			pcap_next_ex(adhandle, &hdr, &p);
			fpgaframeType = -1;
			if (hdr->caplen == 0 || (!p))
			{
				p = 0;
				Clear();
			}
			else if (p)
			{
				if (memcmp(p, UpdateFrameSurMac, sizeof(UpdateFrameSurMac)) == 0)
				{
					fpgaframeType = 0;
					memcpy(frame, p, hdr->caplen);
					return writer = hdr->caplen;
				}
				else if (memcmp(p, UpdateFrameN2SurMac, sizeof(UpdateFrameN2SurMac)) == 0)
				{
					fpgaframeType = 1;
					memcpy(frame, p, hdr->caplen);
					return writer = hdr->caplen;
				}
			}
			else
			{
				break;
			}
			uint32 delta = HwUsCnt() - us;
			if (delta < Ms)
			{
				MsSleep(1);
				continue;
			}
			else
			{
				Clear();
				break;
			}
		}
		return 0;
	}
	void Clear()
	{
		writer = reader = 0;
	}
	void ReadBigEndian(uint16& data)
	{
		uint8* p = (uint8*)&data;
		p[1] = frame[reader];
		p[0] = frame[reader + 1];
		reader += sizeof(data);
	}
	void ReadBigEndian(uint32& data)
	{
		uint8* p = (uint8*)&data;
		p[3] = frame[reader + 0];
		p[2] = frame[reader + 1];
		p[1] = frame[reader + 2];
		p[0] = frame[reader + 3];
		reader += sizeof(data);
	}
	void ReadLittleEndian(uint16& data)
	{
		uint8* p = (uint8*)&data;
		p[0] = frame[reader];
		p[1] = frame[reader + 1];
		reader += sizeof(data);
	}
	void ReadLittleEndian(uint32& data)
	{
		uint8* p = (uint8*)&data;
		p[0] = frame[reader + 0];
		p[1] = frame[reader + 1];
		p[2] = frame[reader + 2];
		p[3] = frame[reader + 3];
		reader += sizeof(data);
	}
	void unPcapN1()
	{
		frameType = cmdType = 0;
		if (fpgaframeType != 0)
		{
			return;
		}
		reader += 14;
		ReadBigEndian(frameType);
		reader += 6;
		ReadBigEndian(cmdType);
	}
	void unPcapN2()
	{
		ctxLen = cmdType = 0;
		if (fpgaframeType != 1)
		{
			return;
		}
		ReadLittleEndian(ctxLen);
		reader += 4;
		ReadLittleEndian(cmdType);
	}
	void unPcap()
	{
		frmOk = 0;
		ethnetType = 0;
		frameType = 0;
		cmdType = 0;
		if (writer == 0)
		{
			return;
		}
		if ((fpgaframeType == 0) && (memcmp(frame, UpdateFrameSurMac, sizeof(UpdateFrameSurMac)) == 0))
		{
			frmOk = 1;
			reader = 12;
			if ((frame[reader] == 0x81) && (frame[reader + 1] == 0x00))
			{
				reader += 4;
			}
			ReadBigEndian(ethnetType);
		}
		else if ((fpgaframeType == 1) && (memcmp(frame, UpdateFrameN2SurMac, sizeof(UpdateFrameN2SurMac)) == 0))
		{
			frmOk = 1;
			reader = 12;
			if ((frame[reader] == 0x81) && (frame[reader + 1] == 0x00))
			{
				reader += 4;
			}
			ReadLittleEndian(ethnetType);
		}
		else
		{
			return;
		}
	}
	uint16 fpgaframeType;
	bool8 frmOk;
	uint16 ethnetType;
	uint16 frameType;
	uint16 cmdType;
	uint16 ctxLen;
};
class InstMainWnd :public MainWnd
{
public:
	InstMainWnd();
	virtual void CheckType(wxCommandEvent& event);
	virtual void TypeChange(wxCommandEvent& event);
	virtual void OpenProgram(wxCommandEvent& event);
	virtual void NetCardChange(wxCommandEvent& event);
	virtual void ReFreshNetCard(wxCommandEvent& event);
	virtual void StartUpdate(wxCommandEvent& event);
	pcap_t* OpenAdHandle();
	void LogInfo(const char* Info);
	void ClearAd();
	void SendLinkAsk();
	bool8 AskForUpdateN1();
	void SendFrameCmdN1(uint16 Cmd);
	void SendFrameCmdN2(uint16 Cmd);
	bool8 SendDataAndWaitRspN1(uint32 FrmTotal, uint32 FrmNo, uint32 FrmOffSet, uint32 FrmLen);
	bool8 GetCheckSumN1(uint32& Sum);
	void FpgaN1Update();
	void FpgaN2Update();
	bool8 WaitForN2ACK(RecvFrame& rframe, uint16 Cmd, uint32 Ms);
protected:
	bool8 isUpdating;
	ProgData prgData;
	pcap_t* adhandle;
	uint16 iedType;
	uint16 prgState;
};
