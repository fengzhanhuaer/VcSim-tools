#pragma once
#include"MainWnd.h"

class InstMainWnd :public MainWnd
{
public:
	InstMainWnd();
	virtual void AddBoot0(wxCommandEvent& event) {
		event.Skip();
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.bin)|*.bin", wxFD_FILE_MUST_EXIST);
		if (dialog.ShowModal() == wxID_OK)
		{
			wxString path = dialog.GetPath();
			int filterIndex = dialog.GetFilterIndex();
			m_textCtrl1->SetLabelText(path);
			m_textCtrl1->SetSelection(path.Len(), path.Len() + 1);
		}
		else
		{
			return;
		}
	}
	virtual void AddUboot(wxCommandEvent& event) {
		event.Skip();
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.bin)|*.bin", wxFD_FILE_MUST_EXIST);
		if (dialog.ShowModal() == wxID_OK)
		{
			wxString path = dialog.GetPath();
			int filterIndex = dialog.GetFilterIndex();
			m_textCtrl2->SetLabelText(path);
			m_textCtrl2->SetSelection(path.Len(), path.Len() + 1);
		}
		else
		{
			return;
		}
	}
	virtual void AddSylix(wxCommandEvent& event) {
		event.Skip();
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.bin)|*.bin", wxFD_FILE_MUST_EXIST);
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
	}
	virtual void CreateBin(wxCommandEvent& event) {
		event.Skip();
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.bin)|*.bin", wxFD_SAVE);
		if (dialog.ShowModal() == wxID_OK)
		{
		}
		else
		{
			return;
		}
		FILE* dstFile = fopen(dialog.GetPath(), "wb");
		if (dstFile == 0)
		{
			return;
		}
		addBin(m_textCtrl1->GetLabelText(), dstFile);
		addBin(m_textCtrl2->GetLabelText(), dstFile);
		char buf[1024] = { 0 };
		for (size_t i = 0; i < 256; i++)
		{
			fwrite(buf, 1, sizeof(buf), dstFile);
		}
		addBin(m_textCtrl3->GetLabelText(), dstFile);
		addBin(m_textCtrl3->GetLabelText(), dstFile);
		fclose(dstFile);
	}
	int addBin(const char* Sur, FILE* bin)
	{
		FILE* surFile = fopen(Sur, "rb");
		if (surFile)
		{
			char buf[4096];
			int len = 0;
			while (0 < (len = fread(buf, 1, sizeof(buf), surFile)))
			{
				fwrite(buf, 1, len, bin);
			}
			fclose(surFile);
			return 0;
		}
		return -1;
	}
protected:

};
