#pragma once
using namespace spt;
#include"tinyxml2\tinyxml2.h"
#include<vector>

union EthFrame
{
	uint8 frameBuf[1600];
	struct stFrame
	{
		uint8 dst[6];
		uint8 sur[6];
		uint8 type[2];
	}st;
};
struct EthFrameHdr
{
	pcap_pkthdr hdr;
	EthFrame frame;
};
typedef std::vector<EthFrameHdr> EthFrameArray;
uint16 GetEthnetType(const uint8* EhnetPcak);
#ifndef CLASS_Info
#define CLASS_Info(InClassName) \
static const char* ClassName() {return #InClassName; };\
virtual const char* InstClassName() { return #InClassName; };
#endif
struct PcapDesNodeInstDriver
{
	const char* Name;
	const char* Des;
	class PcapDesNode* (*Creat)(const char* Des);
};
class  PcapDesNode
{
public:
	enum FilterType
	{
		E_Null,
		E_Equal,
		E_NotEqual,
		E_LellThan,
		E_GreatThan,
	};
public:
	CLASS_Info(PcapDesNode);
public:
	PcapDesNode(const char* Name)
	{
		child = next = 0;
		StrNCpy(des, Name, sizeof(des));
		isLittleEndian = 1;
		isOptional = 0;
		len = 0;
		ctxtag.value.u64 = 0;
		ctxtag.valueInfo1 = 0;//是否有tag
		ctxtag.valueInfo2 = 0;//tagLen
	}
	virtual ~PcapDesNode() {}
	bool LinkNext(PcapDesNode* Next);
	bool AddChild(PcapDesNode* Child);
	const char* Des() { return des; };
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd);
	virtual int Filter(EthFrameHdr* hdr, void* ctx, void*& ctxEnd) { return 1; };
	virtual void Len2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd);
	bool8 SetLittleEndian(bool Is) { return isLittleEndian = Is; }
	bool8 SetOptional(bool Is) { return isOptional = Is; }
	bool8 SetHasTag(bool Is) { return ctxtag.valueInfo1 = Is; }
	bool8 SetTagLen(uint32 Len) { return ctxtag.valueInfo2 = Len; }
	bool8 SetTagValue(uint64 Val) { ctxtag.value.u64 = Val;  return  1; }
	virtual void SetFilter(bool Enable, FilterType Type, const char* Ctx);
	virtual void Save2Xml(tinyxml2::XMLDocument* Doc, tinyxml2::XMLNode* Parent);
	virtual void FreeAllNode();
	PcapDesNode* Next() { return next; };
	PcapDesNode* Child() { return child; };
	bool8 IsTag32Right(void* ctx)
	{
		uint32 tag;
		if (isLittleEndian)
		{
			memcpy(&tag, ctx, sizeof(tag));
		}
		else
		{
			ChangeEndian(&tag, ctx, sizeof(tag));
		}
		return ctxtag.value.u32 == tag;
	}
	bool8 IsTag16Right(void* ctx)
	{
		uint16 tag;
		if (isLittleEndian)
		{
			memcpy(&tag, ctx, sizeof(tag));
		}
		else
		{
			ChangeEndian(&tag, ctx, sizeof(tag));
		}

		return ctxtag.value.u16 == tag;
	}
	bool8 IsTag8Right(void* ctx)
	{
		uint8 tag;
		if (isLittleEndian)
		{
			memcpy(&tag, ctx, sizeof(tag));
		}
		else
		{
			ChangeEndian(&tag, ctx, sizeof(tag));
		}
		return ctxtag.value.u8 == tag;
	}
	bool8 IsTagRight(void* ctx)
	{
		if (ctxtag.valueInfo1)
		{
			switch (ctxtag.valueInfo2)
			{
			case 1:
				return IsTag8Right(ctx);
			case 2:
				return IsTag16Right(ctx);
			case 4:
				return IsTag32Right(ctx);
			default:
				return 0;
				break;
			}
		}
		return 1;
	}
	SalString& FrmDes() { return frmDes; };
	int CtxFrom() { return ctxfrom; };
	int CtxEnd() { return ctxend; };
public:
	st64value UsrPri;
protected:
	void UpdateLocalInfo(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		this->hdr = hdr;
		spt::uint8* header = (spt::uint8*)hdr->frame.frameBuf;
		(this->ctx) = (spt::uint8*)ctx;
		spt::uint8* from = (spt::uint8*)ctx;
		spt::uint8* to = (spt::uint8*)ctxEnd;
		ctxfrom = from - header;
		ctxend = to - header;
	}
protected:
	bool enableFilter;
	FilterType filterType;
	String5000B filterStr;
	st64value filterValue;
	int len;
	EthFrameHdr* hdr;
	spt::uint8* ctx;
	int ctxfrom;
	int ctxend;
	char des[40];
	bool8 isLittleEndian;
	bool8 isOptional;
	st64value value;
	st64value ctxtag;
	PcapDesNode* next;
	PcapDesNode* child;
	String5000B frmDes;
};

class  PcapDesMacNode :public PcapDesNode
{
public:
	PcapDesMacNode(const char* Name) :PcapDesNode(Name) { len = 6; }
	CLASS_Info(PcapDesMacNode);
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + 6;
		frmDes.Clear();
		UpdateLocalInfo(hdr, ctx, ctxEnd);
		Len2String(hdr, ctx, ctxEnd);
		frmDes.FormatHex(pu8[0]) << ".";
		frmDes.FormatHex(pu8[1]) << ".";
		frmDes.FormatHex(pu8[2]) << ".";
		frmDes.FormatHex(pu8[3]) << ".";
		frmDes.FormatHex(pu8[4]) << ".";
		frmDes.FormatHex(pu8[5]);
	}
	virtual int Filter(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + 6;
		if (enableFilter)
		{
			if (filterType == E_Equal)
			{
				if ((filterValue.value.u8bytes.u8[0] == pu8[0])
					&& (filterValue.value.u8bytes.u8[1] == pu8[1])
					&& (filterValue.value.u8bytes.u8[2] == pu8[2])
					&& (filterValue.value.u8bytes.u8[3] == pu8[3])
					&& (filterValue.value.u8bytes.u8[4] == pu8[4])
					&& (filterValue.value.u8bytes.u8[5] == pu8[5])
					)
				{
					return 1;
				}
				return 0;
			}
			if (filterType == E_NotEqual)
			{
				if ((filterValue.value.u8bytes.u8[0] != pu8[0])
					|| (filterValue.value.u8bytes.u8[1] != pu8[1])
					|| (filterValue.value.u8bytes.u8[2] != pu8[2])
					|| (filterValue.value.u8bytes.u8[3] != pu8[3])
					|| (filterValue.value.u8bytes.u8[4] != pu8[4])
					|| (filterValue.value.u8bytes.u8[5] != pu8[5])
					)
				{
					return 1;
				}
				return 0;
			}
		}
		return 1;
	}
	virtual void SetFilter(bool Enable, FilterType Type, const char* Ctx)
	{
		enableFilter = Enable;
		filterType = Type;
		filterStr = Ctx;
		TransString ts;
		ts.SetBuf(Ctx);
		filterValue.value.u8bytes.u8[0] = (uint8)ts.GetHex('.', 3);
		filterValue.value.u8bytes.u8[1] = (uint8)ts.GetHex('.', 3);
		filterValue.value.u8bytes.u8[2] = (uint8)ts.GetHex('.', 3);
		filterValue.value.u8bytes.u8[3] = (uint8)ts.GetHex('.', 3);
		filterValue.value.u8bytes.u8[4] = (uint8)ts.GetHex('.', 3);
		filterValue.value.u8bytes.u8[5] = (uint8)ts.GetHex('.', 3);
	}
};
class  PcapBit64ValueBaseNode :public PcapDesNode
{
public:
	PcapBit64ValueBaseNode(const char* Name) :PcapDesNode(Name) { len = 0; }
	virtual int Filter(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + len;
		st64value Value;
		GetValue(Value, ctx);
		if (enableFilter)
		{
			if (value.valueType == E_SVT_U64)
			{
				if (filterType == E_Equal)
				{
					if ((filterValue.value.u64 == Value.value.u64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_NotEqual)
				{
					if ((filterValue.value.u64 != Value.value.u64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_LellThan)
				{
					if ((filterValue.value.u64 > Value.value.u64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_GreatThan)
				{
					if ((filterValue.value.u64 < Value.value.u64)
						)
					{
						return 1;
					}
					return 0;
				}
			}
			else
			{
				if (filterType == E_Equal)
				{
					if ((filterValue.value.i64 == Value.value.i64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_NotEqual)
				{
					if ((filterValue.value.i64 != Value.value.i64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_LellThan)
				{
					if ((filterValue.value.i64 > Value.value.i64)
						)
					{
						return 1;
					}
					return 0;
				}
				if (filterType == E_GreatThan)
				{
					if ((filterValue.value.i64 < Value.value.i64)
						)
					{
						return 1;
					}
					return 0;
				}
			}
		}
		return 1;
	}
	virtual void SetFilter(bool Enable, FilterType Type, const char* Ctx)
	{
		enableFilter = Enable;
		filterType = Type;
		filterStr = Ctx;
		TransString ts;
		ts.SetBuf(Ctx);
		if ((value.valueType == E_SVT_U64))
		{
			filterValue.value.i64 = ts.GetUInt64(0);
		}
		else
		{
			filterValue.value.i64 = ts.GetInt64(0);
		}

	}
	void GetValue(st64value& Value, void* ctx)
	{
		Value.value.i64 = 0;
		if ((value.valueType == E_SVT_U8)
			|| (value.valueType == E_SVT_U16)
			|| (value.valueType == E_SVT_U32)
			|| (value.valueType == E_SVT_U64))
		{
			if (isLittleEndian)
			{
				MemCpy(&Value.value.i8, ctx, len);
			}
			else
			{
				ChangeEndian(&Value.value.i8, ctx, len);
			}
		}
		else
		{
			st64value Val;
			if (isLittleEndian)
			{
				MemCpy(&Val.value.i8, ctx, len);
			}
			else
			{
				ChangeEndian(&Val.value.i8, ctx, len);
			}
			if (value.valueType == E_SVT_I8)
			{
				Value.value.i64 = Value.value.i8;
			}
			else if (value.valueType == E_SVT_I16)
			{
				Value.value.i64 = Value.value.i16;
			}
			else if (value.valueType == E_SVT_I32)
			{
				Value.value.i64 = Value.value.i32;
			}
			else if (value.valueType == E_SVT_I64)
			{
				Value.value.i64 = Value.value.i64;
			}

		}
	}
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* ptr = (decltype(ptr))ctx;
		ctxEnd = ptr + len;
		frmDes.Clear();
		UpdateLocalInfo(hdr, ctx, ctxEnd);
		if ((uint32)this->ctxend >= hdr->hdr.caplen)
		{
			frmDes.Clear();
			return;
		}
		st64value Value;
		GetValue(Value, ctx);
		if (value.valueType == E_SVT_U64)
		{
			frmDes << Value.value.u64 << " ";
		}
		else
		{
			frmDes << Value.value.i64 << " ";
		}
	}
};
class  PcapUInt8ValueNode :public PcapBit64ValueBaseNode
{
public:
	PcapUInt8ValueNode(const char* Name) :PcapBit64ValueBaseNode(Name) { value.valueType = E_SVT_U8; len = 1; }
	CLASS_Info(PcapUInt8ValueNode);
};
class  PcapUInt16ValueNode :public PcapBit64ValueBaseNode
{
public:
	PcapUInt16ValueNode(const char* Name) :PcapBit64ValueBaseNode(Name) {
		value.valueType = E_SVT_U16; len = 2;
	}
	CLASS_Info(PcapUInt16ValueNode);
};
class  PcapUInt32ValueNode :public PcapBit64ValueBaseNode
{
public:
	PcapUInt32ValueNode(const char* Name) :PcapBit64ValueBaseNode(Name) {
		value.valueType = E_SVT_U32; len = 4;
	}
	CLASS_Info(PcapUInt32ValueNode);
};
class  PcapUInt64ValueNode :public PcapBit64ValueBaseNode
{
public:
	PcapUInt64ValueNode(const char* Name) :PcapBit64ValueBaseNode(Name) {
		value.valueType = E_SVT_U64; len = 8;
	}
	CLASS_Info(PcapUInt64ValueNode);
};
class  PcapInt8ValueNode :public PcapBit64ValueBaseNode
{
public:
	PcapInt8ValueNode(const char* Name) :PcapBit64ValueBaseNode(Name) {
		value.valueType = E_SVT_I8; len = 1;
	}
	CLASS_Info(PcapInt8ValueNode);
};
class  PcapInt16ValueNode :public PcapDesNode
{
public:
	PcapInt16ValueNode(const char* Name) :PcapDesNode(Name) {
		value.valueType = E_SVT_I16; len = 2;
	}
	CLASS_Info(PcapInt16ValueNode);
};
class  PcapInt32ValueNode :public PcapDesNode
{
public:
	PcapInt32ValueNode(const char* Name) :PcapDesNode(Name) {
		value.valueType = E_SVT_I32; len = 4;
	}
	CLASS_Info(PcapInt32ValueNode);
};
class  PcapInt64ValueNode :public PcapDesNode
{
public:
	PcapInt64ValueNode(const char* Name) :PcapDesNode(Name) {
		value.valueType = E_SVT_I64; len = 8;
	}
	CLASS_Info(PcapInt64ValueNode);
};
class  PcapBit64HexBaseNode :public PcapDesNode
{
public:
	PcapBit64HexBaseNode(const char* Name) :PcapDesNode(Name) { len = 0; }
	virtual int Filter(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + len;
		st64value Value;
		GetValue(Value, ctx);
		if (enableFilter)
		{
			if (filterType == E_Equal)
			{
				if ((filterValue.value.u64 == Value.value.u64)
					)
				{
					return 1;
				}
				return 0;
			}
			if (filterType == E_NotEqual)
			{
				if ((filterValue.value.u64 != Value.value.u64)
					)
				{
					return 1;
				}
				return 0;
			}
			if (filterType == E_LellThan)
			{
				if ((filterValue.value.u64 > Value.value.u64)
					)
				{
					return 1;
				}
				return 0;
			}
			if (filterType == E_GreatThan)
			{
				if ((filterValue.value.u64 < Value.value.u64)
					)
				{
					return 1;
				}
				return 0;
			}
		}
		return 1;
	}
	virtual void SetFilter(bool Enable, FilterType Type, const char* Ctx)
	{
		enableFilter = Enable;
		filterType = Type;
		filterStr = Ctx;
		TransString ts;
		ts.SetBuf(Ctx);
		filterValue.value.u64 = ts.GetHex(0, 16);
	}
	void GetValue(st64value& Value, void* ctx)
	{
		Value.value.u64 = 0;
		if (isLittleEndian)
		{
			MemCpy(&Value.value.i8, ctx, len);
		}
		else
		{
			ChangeEndian(&Value.value.i8, ctx, len);
		}
	}
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		spt::uint8* ptr = (decltype(ptr))ctx;
		ctxEnd = ptr + len;
		frmDes.Clear();
		UpdateLocalInfo(hdr, ctx, ctxEnd);
		if ((uint32)this->ctxend >= hdr->hdr.caplen)
		{
			frmDes.Clear();
			return;
		}
		st64value Value;
		GetValue(Value, ctx);
		if (value.valueType == E_SVT_HEX8)
		{
			spt::String1000B  Str;
			Str.FormatHex(Value.value.u8);
			frmDes << Str.Str() << " ";
		}
		else if (value.valueType == E_SVT_HEX16)
		{
			spt::String1000B  Str;
			Str.FormatHex(Value.value.u16);
			frmDes << Str.Str() << " ";
		}
		else if (value.valueType == E_SVT_HEX32)
		{
			spt::String1000B  Str;
			Str.FormatHex(Value.value.u32);
			frmDes << Str.Str() << " ";
		}
		else if (value.valueType == E_SVT_HEX64)
		{
			spt::String1000B  Str;
			Str.FormatHex(Value.value.u64);
			frmDes << Str.Str() << " ";
		}
	}
};
class  PcapHex8ValueNode :public PcapBit64HexBaseNode
{
public:
	PcapHex8ValueNode(const char* Name) :PcapBit64HexBaseNode(Name) {
		value.valueType = E_SVT_HEX8; len = 1;
	}
	CLASS_Info(PcapHex8ValueNode);
};
class  PcapHex16ValueNode :public PcapBit64HexBaseNode
{
public:
	PcapHex16ValueNode(const char* Name) :PcapBit64HexBaseNode(Name) {
		value.valueType = E_SVT_HEX16; len = 2;
	}
	CLASS_Info(PcapHex16ValueNode);
};
class  PcapHex32ValueNode :public PcapBit64HexBaseNode
{
public:
	PcapHex32ValueNode(const char* Name) :PcapBit64HexBaseNode(Name) {
		value.valueType = E_SVT_HEX32; len = 4;
	}
	CLASS_Info(PcapHex32ValueNode);
};
class  PcapHex64ValueNode :public PcapBit64HexBaseNode
{
public:
	PcapHex64ValueNode(const char* Name) :PcapBit64HexBaseNode(Name) {
		value.valueType = E_SVT_HEX64; len = 8;
	}
	CLASS_Info(PcapHex64ValueNode);
};
class  PcapDesVlanNode :public PcapDesNode
{
public:
	PcapDesVlanNode(const char* Name) :PcapDesNode(Name)
	{
		SetLittleEndian(0);
		SetOptional(1);
		SetHasTag(1);
		SetTagValue(0x8100);
		SetTagLen(2);
		len = 4;
		vlan = new PcapHex16ValueNode("");
		vlan->SetLittleEndian(0);
		vlan->SetOptional(0);
	}
	virtual ~PcapDesVlanNode()
	{
		delete vlan;
	}
	CLASS_Info(PcapDesVlanNode);
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		if (IsTagRight(ctx) == 0)
		{
			frmDes.Clear();
			return;
		}
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + 2;
		UpdateLocalInfo(hdr, ctx, ctxEnd);
		if ((uint32)this->ctxend >= hdr->hdr.caplen)
		{
			frmDes.Clear();
			return;
		}
		frmDes.Clear();
		Len2String(hdr, ctx, ctxEnd);
		spt::String1000B  Str;
		Str << " Tag(";
		Str.FormatHex(pu8[0]).FormatHex(pu8[1]) << ") ";
		vlan->Ctx2String(hdr, ctxEnd, ctxEnd);
		frmDes << Str.Str() << vlan->FrmDes();
	}
private:
	PcapHex16ValueNode* vlan;
};
class  PcapDesPriUtcNode :public PcapDesNode
{
public:
	PcapDesPriUtcNode(const char* Name) :PcapDesNode(Name)
	{
		len = 8;
		SetLittleEndian(1);
		SetOptional(0);
		SetHasTag(0);
		SetTagValue(0);
		SetTagLen(0);
	}
	CLASS_Info(PcapDesPriUtcNode);
	virtual void Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
	{
		if (IsTagRight(ctx) == 0)
		{
			frmDes.Clear();
			return;
		}
		spt::uint8* pu8 = (spt::uint8*)ctx;
		ctxEnd = pu8 + len;
		UpdateLocalInfo(hdr, ctx, ctxEnd);
		if ((uint32)this->ctxend >= hdr->hdr.caplen)
		{
			frmDes.Clear();
			return;
		}
		frmDes.Clear();
		Len2String(hdr, ctx, ctxEnd);
		spt::String1000B  Str;

		SalStdUtcStamp stamp;
		MemCpy(&stamp, ctx, len);
		SalDateStamp lstamp;
		lstamp.fromPriUtcCode(stamp.uSec, stamp.u_Fra_Q);
		lstamp.ToStrHzFmt3(Str);
		Str << " Q(";
		Str.FormatHex((uint8)stamp.u_Fra_Q) << ")";
		frmDes << Str.Str();
	}
private:

};
class PcapDesFile
{
public:
	PcapDesFile();
	static PcapDesNode* CreatNode(const char* ClassName, const char* Des, bool8 isLittlEndian = 1, bool8 isOptional = 0);
	void FreeAllNode();
	void AddNext(PcapDesNode* Child);
	PcapDesNode* Root() { return root; };
	int32 SaveXml(const char* Name);
	int32 LoadXml(const char* Name);
	void LoadNode(tinyxml2::XMLElement* Node, PcapDesNode* NodeP, PcapDesFile* File);
	int Update(EthFrameHdr& Hdr);
	//1成功0失败
	int Filter(EthFrameHdr& Hdr);
protected:
	int UpdateNode(PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd);
	int FilterNode(PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd);
protected:
	EthFrameHdr Hdr;
	PcapDesNode* root;
};
