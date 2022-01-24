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
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxNotebook* RecvBook;
		wxPanel* m_panel1;
		wxButton* m_button1;
		wxChoice* m_choice1;
		wxButton* m_button2;
		wxButton* m_button3;
		wxButton* m_button4;
		wxButton* m_button5;
		wxButton* m_button6;
		wxCheckBox* m_checkBox1;
		wxChoice* m_choice2;
		wxChoice* m_choice3;
		wxTextCtrl* m_textCtrl1;
		wxCheckBox* m_checkBox11;
		wxChoice* m_choice4;
		wxChoice* m_choice5;
		wxTextCtrl* m_textCtrl4;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel2;
		wxGrid* m_grid1;
		wxPanel* m_panel3;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel4;
		wxTextCtrl* m_textCtrl5;
		wxPanel* m_panel5;
		wxTreeCtrl* m_treeCtrl1;
		wxTimer m_timer1;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, override them in your derived class
		virtual void UpdateOnIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void ReFreshGnrNetCard( wxCommandEvent& event ) { event.Skip(); }
		virtual void StartGnrCapture( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearGnrFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void LoadGnrCfg( wxCommandEvent& event ) { event.Skip(); }
		virtual void SaveGnrPcap( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateGnrFilter1( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateGnrFilter2( wxCommandEvent& event ) { event.Skip(); }
		virtual void ShowGnrSelFrame( wxGridEvent& event ) { event.Skip(); }
		virtual void UpDateUi10Ms( wxTimerEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NetCapture"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1375,702 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWnd();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 0 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::m_splitter1OnIdle ), NULL, this );
		}

		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 0 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( MainWnd::m_splitter2OnIdle ), NULL, this );
		}

};

