///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/timectrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxDialog
{
	private:

	protected:
		wxTextCtrl* Path;
		wxButton* Select;
		wxChoice* GngType;
		wxChoice* ProgramType;
		wxTextCtrl* ProgramName;
		wxStaticText* m_staticText3;
		wxSpinCtrl* sizeM;
		wxSpinCtrl* sizeK;
		wxSpinCtrl* sizeB;
		wxTextCtrl* Prger;
		wxStaticText* m_staticText2;
		wxSpinCtrl* Vmajor;
		wxSpinCtrl* Vminor;
		wxSpinCtrl* Vdel;
		wxDatePickerCtrl* m_datePicker1;
		wxTimePickerCtrl* m_timePicker1;
		wxStaticText* Crc;
		wxTextCtrl* tCrc;
		wxButton* m_button2;
		wxButton* m_button3;

		// Virtual event handlers, override them in your derived class
		virtual void SelectFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void TypeChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void readfromfile( wxCommandEvent& event ) { event.Skip(); }
		virtual void creatfile( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("FileAddVer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 548,259 ), long style = wxDEFAULT_DIALOG_STYLE );

		~MainWnd();

};

