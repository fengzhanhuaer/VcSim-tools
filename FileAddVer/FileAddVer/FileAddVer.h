#pragma once
#include<wx/wx.h>
#include"MainWnd.h"
#include"ApiProject.h"
using namespace spt;
class MainApp : public wxApp
{
public:
	virtual bool OnInit();
protected:
	class MainWndInst* wnd;
};
class MainWndInst :public MainWnd
{
public:
	MainWndInst() :MainWnd(0) {}
protected:
	// Virtual event handlers, override them in your derived class
	virtual void SelectFile(wxCommandEvent& event)
	{
		wxFileDialog dialog(this, "Select a file", ".", "",
			"Files (*.*)|*.*", wxFD_FILE_MUST_EXIST);
		if (dialog.ShowModal() == wxID_OK)
		{
			wxString path = dialog.GetPath();
			int filterIndex = dialog.GetFilterIndex();
			Path->SetLabelText(path);
			Path->SetSelection(path.Len(), path.Len() + 1);
		}
		event.Skip();
	}
	virtual void TypeChange(wxCommandEvent& event)
	{
		if (GngType->GetStringSelection() == "新一代")
		{
			if (ProgramType->GetStringSelection() == "自定义")
			{

			}
			else if (ProgramType->GetStringSelection() == "Sylix.T3BSP.Gzk")
			{
				ProgramName->SetLabelText(ProgramType->GetStringSelection());
				sizeM->SetValue(5);
				sizeK->SetValue(0);
				sizeB->SetValue(0);
			}
			else if (ProgramType->GetStringSelection() == "Sylix.Boot0")
			{
				ProgramName->SetLabelText(ProgramType->GetStringSelection());
				sizeM->SetValue(0);
				sizeK->SetValue(64);
				sizeB->SetValue(0);
			}
			else if (ProgramType->GetStringSelection() == "Sylix.UBoot")
			{
				ProgramName->SetLabelText(ProgramType->GetStringSelection());
				sizeM->SetValue(1);
				sizeK->SetValue(704);
				sizeB->SetValue(0);
			}
		}
		event.Skip();
	}
	virtual void readfromfile(wxCommandEvent& event)
	{
		ProgBinFile file;
		SptVersion version;
		String100B fmt;
		if (file.GetVersion(Path->GetLabelText(), version))
		{
			fmt.Clear();
			fmt.FormatHex((uint16)version.crc);
			tCrc->SetLabelText(fmt.Str());
			Vmajor->SetValue(version.major);
			Vminor->SetValue(version.minor);
			Vdel->SetValue(version.reversion);
			ProgramName->SetLabelText(version.programName);
			Prger->SetLabelText(version.publisher);
			sizeM->SetValue(version.fileSize / 1024 / 1024);
			sizeK->SetValue(version.fileSize / 1024 % 1024);
			sizeB->SetValue(version.fileSize % 1024);
			SalDateStamp stamp;
			stamp.Set(version.datetimeus);
			wxDateTime date = wxDateTime(stamp.toUtcSec());
			m_datePicker1->SetValue(date);
			m_timePicker1->SetValue(date);
		}
		event.Skip();
	}
	virtual void creatfile(wxCommandEvent& event)
	{
		ProgBinFile file;
		SptVersion version;
		String100B fmt;
		MemSet(&version, 0, sizeof(version));
		SalDateStamp stamp;
		version.FillInfo(sizeM->GetValue() * 1024 * 1024 + sizeK->GetValue() * 1024 + sizeB->GetValue(),
			Vmajor->GetValue(),
			Vminor->GetValue(),
			Vdel->GetValue(),
			ProgramName->GetLabelText(),
			Prger->GetLabelText(),
			stamp.fromUtcSec(m_datePicker1->GetValue().GetDateOnly().GetTicks() + m_timePicker1->GetValue().GetTicks() - m_timePicker1->GetValue().GetDateOnly().GetTicks())
		);
		file.CreatBin(Path->GetLabelText(), version);
		fmt.Clear();
		fmt.FormatHex((uint16)version.crc);
		tCrc->SetLabelText(fmt.Str());
		event.Skip();
	}
};
