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
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxButton* m_button1;
		wxTextCtrl* m_textCtrl2;
		wxStaticText* m_staticText4;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText2;
		wxSpinCtrl* m_spinCtrl2;
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl3;
		wxButton* m_button2;
		wxButton* m_button3;
		wxTextCtrl* m_textCtrl1;

		// Virtual event handlers, override them in your derived class
		virtual void OpenPrg( wxCommandEvent& event ) { event.Skip(); }
		virtual void CreatPrg( wxCommandEvent& event ) { event.Skip(); }
		virtual void CheckPrg( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 554,305 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainWnd();

};

