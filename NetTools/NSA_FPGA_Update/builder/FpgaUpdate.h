///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText41;
		wxStaticText* m_staticText1;
		wxButton* m_button1;
		wxTextCtrl* m_textCtrl1;
		wxChoice* m_choice1;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrl3;
		wxButton* m_button2;
		wxStaticText* m_staticText4;
		wxChoice* m_choice2;
		wxButton* m_button4;
		wxButton* m_button3;
		wxTextCtrl* m_textCtrl4;

		// Virtual event handlers, override them in your derived class
		virtual void CheckType( wxCommandEvent& event ) { event.Skip(); }
		virtual void TypeChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenProgram( wxCommandEvent& event ) { event.Skip(); }
		virtual void NetCardChange( wxCommandEvent& event ) { event.Skip(); }
		virtual void ReFreshNetCard( wxCommandEvent& event ) { event.Skip(); }
		virtual void StartUpdate( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NsaFpgaUpdate"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 485,507 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL );

		~MainWnd();

};

