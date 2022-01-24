#include"Main.h"

#define CreatInstDriver(Class,ClassDes)	Class::ClassName(),ClassDes,[](const char* Des) {return (PcapDesNode*)(Class*)new Class(Des); }
PcapDesNodeInstDriver DesNodeInstDriver[] =
{
	{CreatInstDriver(PcapDesNode,"空节点")},
	{CreatInstDriver(PcapDesMacNode,"MAC地址")},
	{CreatInstDriver(PcapUInt8ValueNode,"无符号8位")},
	{CreatInstDriver(PcapUInt16ValueNode,"无符号16位")},
	{CreatInstDriver(PcapUInt32ValueNode,"无符号32位")},
	{CreatInstDriver(PcapUInt64ValueNode,"无符号64位")},
	{CreatInstDriver(PcapInt8ValueNode,"有符号8位")},
	{CreatInstDriver(PcapInt16ValueNode,"有符号16位")},
	{CreatInstDriver(PcapInt32ValueNode,"有符号32位")},
	{CreatInstDriver(PcapInt64ValueNode,"有符号64位")},
	{CreatInstDriver(PcapHex8ValueNode,"16进制8位")},
	{CreatInstDriver(PcapHex16ValueNode,"16进制16位")},
	{CreatInstDriver(PcapHex32ValueNode,"16进制32位")},
	{CreatInstDriver(PcapHex64ValueNode,"16进制64位")},
	{CreatInstDriver(PcapDesVlanNode,"VLAN")},
	{CreatInstDriver(PcapDesPriUtcNode,"私有UTC时间戳")},
};
const int DesNodeInstDriverNum = M_ArrLen(DesNodeInstDriver);
PcapDesFile::PcapDesFile()
{
	root = 0;
}

PcapDesNode* PcapDesFile::CreatNode(const char* ClassName, const char* Des, bool8 isLittlEndian, bool8 isOptional)
{
	for (int i = 0; i < DesNodeInstDriverNum; i++)
	{
		if (StrCmp(ClassName, DesNodeInstDriver[i].Name) == 0)
		{
			PcapDesNode* ptr = DesNodeInstDriver[i].Creat(Des);
			const char* instName = ptr->InstClassName();
			ptr->SetLittleEndian(isLittlEndian);
			ptr->SetOptional(isOptional);
			return ptr;
		}
	}
	return 0;
}

void PcapDesFile::FreeAllNode()
{
	if (root)
	{
		root->FreeAllNode();
		delete root;
		root = 0;
	}
}


void PcapDesFile::AddNext(PcapDesNode* Child)
{
	if (root)
	{
		root->AddChild(Child);
	}
	else
	{
		root = Child;
	}
}

int32 PcapDesFile::SaveXml(const char* Name)
{
	if (root)
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLDeclaration* del = doc.NewDeclaration("xml version=\"1.0\" encoding=\"GB2312\"");
		doc.LinkEndChild(del);
		tinyxml2::XMLElement* xroot = doc.NewElement("Frame");
		root->Save2Xml(&doc, xroot);
		doc.LinkEndChild(xroot);
		tinyxml2::XMLElement* xdata = doc.NewElement("DataType");
		for (int i = 0; i < DesNodeInstDriverNum; i++)
		{
			tinyxml2::XMLElement* Type = doc.NewElement("Type");
			Type->SetAttribute("ClassName", DesNodeInstDriver[i].Name);
			Type->SetAttribute("Des", DesNodeInstDriver[i].Des);
			xdata->LinkEndChild(Type);
		}
		doc.LinkEndChild(xdata);
		doc.SaveFile(Name);
	}
	return 0;
}

int32 PcapDesFile::LoadXml(const char* Name)
{
	if (root)
	{
		FreeAllNode();
		root = 0;
	}
	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(Name) != 0)
	{
		return -1;
	}
	tinyxml2::XMLElement* xroot = doc.FirstChildElement("Frame");
	if (!xroot)
	{
		return -1;
	}
	tinyxml2::XMLElement* element = xroot->FirstChildElement("Inst");
	while (element)
	{
		LoadNode(element, root, this);
		element = element->NextSiblingElement("Inst");
	}
	return 0;
}

void PcapDesFile::LoadNode(tinyxml2::XMLElement* Node, PcapDesNode* NodeP, PcapDesFile* File)
{
	if (!Node)
	{
		return;
	}
	const tinyxml2::XMLAttribute* att;
	if (!(att = Node->FindAttribute("ClassName")))
	{
		return;
	}
	const tinyxml2::XMLAttribute* att2;
	if (!(att2 = Node->FindAttribute("InstName")))
	{
		return;
	}
	PcapDesNode* node = CreatNode(att->Value(), att2->Value());
	if (!node)
	{
		return;
	}
	if (att = Node->FindAttribute("isLittleEndian"))
	{
		node->SetLittleEndian(att->UnsignedValue());
	}
	if (att = Node->FindAttribute("isOptional"))
	{
		node->SetOptional(att->UnsignedValue());
	}
	if (att = Node->FindAttribute("hasTag"))
	{
		node->SetHasTag(att->UnsignedValue());
	}
	if (att = Node->FindAttribute("TagLen"))
	{
		node->SetTagLen(att->UnsignedValue());
	}
	if (att = Node->FindAttribute("TagValue"))
	{
		TransString ts;
		ts.SetBuf(att->Value());
		uint64 data;
		data = ts.GetHex(0, 16);
		node->SetTagValue(data);
	}
	if (NodeP)
	{
		NodeP->AddChild(node);
	}
	else
	{
		AddNext(node);
	}
	tinyxml2::XMLElement* element = Node->FirstChildElement("Inst");
	while (element)
	{
		LoadNode(element, node, File);
		element = element->NextSiblingElement("Inst");
	}
}

int PcapDesFile::Update(EthFrameHdr& Hdr)
{
	this->Hdr = Hdr;
	if (root)
	{
		void* ctxEnd = this->Hdr.frame.frameBuf;
		UpdateNode(root, &this->Hdr, ctxEnd, ctxEnd);
	}
	return 0;
}

int PcapDesFile::Filter(EthFrameHdr& Hdr)
{
	if (root)
	{
		void* ctxEnd = Hdr.frame.frameBuf;
		return FilterNode(root, &Hdr, ctxEnd, ctxEnd);
	}
	return 0;
}

int PcapDesFile::UpdateNode(PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
{
	auto disSingleNode = [](PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd) {
		if (Node)
		{
			Node->Ctx2String(hdr, ctx, ctxEnd);
		}
	};
	if (Node)
	{
		ctxEnd = ctx;
		disSingleNode(Node, hdr, ctxEnd, ctxEnd);
		if (Node->Child())
		{
			PcapDesNode* now = Node->Child();
			while (now)
			{
				UpdateNode(now, hdr, ctxEnd, ctxEnd);
				now = now->Next();
			}
		}
	}
	return 0;
}

int PcapDesFile::FilterNode(PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
{
	int res = 0;
	auto disSingleNode = [](PcapDesNode* Node, EthFrameHdr* hdr, void* ctx, void*& ctxEnd) {
		if (Node)
		{
			return Node->Filter(hdr, ctx, ctxEnd);
		}
		return 0;
	};
	if (Node)
	{
		ctxEnd = ctx;
		res = disSingleNode(Node, hdr, ctxEnd, ctxEnd);
		if (res == 0)
		{
			return 0;
		}
		if (Node->Child())
		{
			PcapDesNode* now = Node->Child();
			while (now)
			{
				res = FilterNode(now, hdr, ctxEnd, ctxEnd);
				if (res == 0)
				{
					return 0;
				}
				now = now->Next();
			}
		}
		return 1;
	}
	return 0;
}

bool PcapDesNode::LinkNext(PcapDesNode* Next)
{
	PcapDesNode* now = this;
	while (now && now->next)
	{
		now = now->next;
	}
	if (now)
	{
		now->next = Next;
	}
	return 1;
}

bool PcapDesNode::AddChild(PcapDesNode* Next)
{
	if (this)
	{
		if (this->child)
		{
			this->child->LinkNext(Next);
		}
		else
		{
			this->child = Next;
		}
	}
	return 0;
}

void PcapDesNode::Ctx2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
{
	frmDes.Clear();
	ctxfrom = this->ctxend = 0;
	this->ctx = (spt::uint8*)ctx;
}

void PcapDesNode::Len2String(EthFrameHdr* hdr, void* ctx, void*& ctxEnd)
{
	frmDes << " Len(" << len << ") ";
}

void PcapDesNode::SetFilter(bool Enable, FilterType Type, const char* Ctx)
{
	enableFilter = Enable;
	filterType = Type;
	filterStr = Ctx;
}

void PcapDesNode::Save2Xml(tinyxml2::XMLDocument* Doc, tinyxml2::XMLNode* Parent)
{
	if (this)
	{
		tinyxml2::XMLElement* node = Doc->NewElement("Inst");
		node->SetAttribute("InstName", Des());
		node->SetAttribute("ClassName", InstClassName());
		node->SetAttribute("isLittleEndian", isLittleEndian);
		node->SetAttribute("isOptional", isOptional);
		node->SetAttribute("hasTag", ctxtag.valueInfo1);
		node->SetAttribute("TagLen", ctxtag.valueInfo2);
		String100B str;
		str.FormatHex(ctxtag.value.u32);
		node->SetAttribute("TagValue", str.Str());
		Parent->LinkEndChild(node);
		if (child)
		{
			PcapDesNode* now = child;
			while (now)
			{
				now->Save2Xml(Doc, node);
				now = now->next;
			}
		}
	}
}

void PcapDesNode::FreeAllNode()
{
	if (this)
	{
		if (child)
		{
			PcapDesNode* now = child;
			while (now)
			{
				now->FreeAllNode();
				PcapDesNode* last = now;
				now = now->next;
				delete last;
			}
		}
	}
}

uint16 GetEthnetType(const uint8* EhnetPcak)
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
