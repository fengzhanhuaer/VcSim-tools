///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/button.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxButton* m_button4;
		wxTextCtrl* m_textCtrl1;
		wxButton* m_button2;
		wxTextCtrl* m_textCtrl2;
		wxButton* m_button5;
		wxTextCtrl* m_textCtrl3;
		wxButton* m_button6;

		// Virtual event handlers, override them in your derived class
		virtual void AddBoot0( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddUboot( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddSylix( wxCommandEvent& event ) { event.Skip(); }
		virtual void CreateBin( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NgsPrgBinMerge"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 539,275 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWnd();

};

