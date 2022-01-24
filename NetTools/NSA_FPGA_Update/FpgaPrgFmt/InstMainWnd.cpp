#include"Main.h"

InstMainWnd::InstMainWnd()
	:MainWnd(0)
{
}

void InstMainWnd::OpenPrg(wxCommandEvent& event)
{
	event.Skip();
	wxFileDialog dialog(this, "Select a file", ".", "",
		"Files (*.*)|*.*", wxFD_FILE_MUST_EXIST);
	if (dialog.ShowModal() == wxID_OK)
	{
		path = dialog.GetPath();
		dir = dialog.GetDirectory();
		int filterIndex = dialog.GetFilterIndex();
		m_textCtrl2->SetLabelText(path);
		m_textCtrl2->SetSelection(path.Len(), path.Len() + 1);
	}
	else
	{
		path = "";
		dir = "";
		return;
	}
}
void InstMainWnd::CreatPrg(wxCommandEvent& event)
{
	event.Skip();
	if (path == "")
	{
		LogMsg("����ѡ���ļ�\n");
		return;
	}
	FILE* file;
	file = fopen(path, "rb");
	if (file)
	{

	}
	else
	{
		LogMsg("���ļ�ʧ��\n");
		return;
	}
	unsigned int totalSize = m_spinCtrl1->GetValue() * 1024 * 1024 + m_spinCtrl2->GetValue() * 1024;
	struct _stat statbuf;
	_stat(path, &statbuf);
	unsigned int filesize = statbuf.st_size;

	if ((filesize) > (totalSize))
	{
		LogMsg("Դ�ļ������趨Ŀ��\n");
		fclose(file);
		return;
	}
	unsigned char* buf = (unsigned char*)calloc(totalSize, 1);
	if (!buf)
	{
		LogMsg("�ڴ�����ʧ��\n");
		fclose(file);
		return;
	}
	memset(buf, 0xff, totalSize);
	fread(buf, 1, filesize, file);
	fclose(file);
	unsigned int sum = 0;
	for (unsigned int i = 0; i < totalSize; i++)
	{
		sum += buf[i];
	}
	unsigned int header[8] = { 0 };
	header[0] = totalSize;
	header[1] = sum;
	wxString name = dir + "\\" + m_textCtrl3->GetLabelText() << ".bin";
	if (name == "")
	{
		name = "ProgramName";
	}
	file = fopen(name, "wb");
	if (!file)
	{
		free(buf);
		LogMsg("����Ŀ���ļ�ʧ��\n");
		return;
	}
	fwrite(header, 1, sizeof(header), file);
	fwrite(buf, 1, totalSize, file);
	fclose(file);

	wxString info = "�������:";
	info << name << " Size:" << m_spinCtrl1->GetValue() << "mb" << m_spinCtrl2->GetValue() << "kb" << " Crc:";
	info << info.Format("%08X", sum) << "\n";
	LogMsg(info);
	free(buf);
}

void InstMainWnd::CheckPrg(wxCommandEvent& event)
{
	event.Skip();
	FILE* file;
	file = fopen(path, "rb");
	if (file)
	{

	}
	else
	{
		LogMsg("���ļ�ʧ��\n");
		return;
	}

	struct _stat statbuf;
	_stat(path, &statbuf);

	unsigned int totalSize = statbuf.st_size;
	if ((totalSize) <= (32))
	{
		LogMsg("�ļ���С\n");
		fclose(file);
		return;
	}
	unsigned char* buf = (unsigned char*)calloc(totalSize, 1);
	if (!buf)
	{
		LogMsg("�ڴ�����ʧ��\n");
		fclose(file);
		return;
	}
	memset(buf, 0x0, totalSize);
	unsigned int header[8] = { 0 };
	unsigned int filesize = statbuf.st_size - sizeof(header);
	fread(header, 1, sizeof(header), file);
	fread(buf, 1, filesize, file);
	fclose(file);
	unsigned int sum = 0;
	for (unsigned int i = 0; i < filesize; i++)
	{
		sum += buf[i];
	}
	if (header[0] != filesize)
	{
		wxString info = "У���쳣:";
		info << "Size:" << header[0] << "!=" << filesize << "\n";;
		LogMsg(info);
	}
	if (header[1] != sum)
	{
		wxString info = "У���쳣:";
		info << "Crc:" << header[1] << "!=" << sum << "\n";;
		LogMsg(info);
	}
	wxString info = "У�����:";
	info << "Size:" << filesize << " Crc:";
	info << info.Format("%08X", sum) << "\n";
	LogMsg(info);
}

void InstMainWnd::LogMsg(const char* Msg)
{
	m_textCtrl1->AppendText(Msg);
	m_textCtrl1->SetSelection(m_textCtrl1->GetLabelText().Len(), m_textCtrl1->GetLabelText().Len() + 1);
}
