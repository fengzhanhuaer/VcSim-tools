///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
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
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class ConsoleWnd
///////////////////////////////////////////////////////////////////////////////
class ConsoleWnd : public wxFrame
{
	private:

	protected:
		wxNotebook* m_notebook2;
		wxPanel* NsaSeries;
		wxNotebook* m_notebook4;
		wxPanel* m_panel3;
		wxButton* m_button1;
		wxPanel* NgsSeries;
		wxNotebook* m_notebook41;
		wxPanel* m_panel31;
		wxButton* m_button2;
		wxPanel* m_panel6;
		wxButton* m_button21;
		wxPanel* GnrTools;
		wxNotebook* m_notebook411;
		wxPanel* m_panel311;
		wxButton* m_button22;
		wxPanel* m_panel19;

		// Virtual event handlers, override them in your derived class
		virtual void OpenNsaFpgaUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenNgsSimLcd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenNgsVerAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenGnrNetCapture( wxCommandEvent& event ) { event.Skip(); }


	public:

		ConsoleWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("IedToolsConsole"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 633,205 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );

		~ConsoleWnd();

};

