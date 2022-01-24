#pragma once

uint32 GetEthnetType(const uint8* EhnetPcak);

struct SvFrame
{
	int32 unpackFrame(const uint8* EhnetPcak);
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
