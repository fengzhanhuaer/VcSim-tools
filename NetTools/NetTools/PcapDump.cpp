#include "Main.h"

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

int32 SvFrame::unpackFrame(const uint8* EhnetPcak)
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
