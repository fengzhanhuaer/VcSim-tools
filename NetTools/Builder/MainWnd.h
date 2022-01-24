///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/menu.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/timer.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxToolBar* m_toolBar1;
		wxChoice* NetCard;
		wxButton* RefreshNetCard;
		wxButton* m_button7;
		wxNotebook* m_notebook1;
		wxPanel* SendPage;
		wxNotebook* sendBook;
		wxPanel* m_panel8;
		wxStaticText* m_staticText31;
		wxSpinCtrlDouble* m_spinCtrlDouble1;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText7;
		wxSpinCtrl* m_spinCtrl3;
		wxButton* m_button11;
		wxTextCtrl* m_textCtrl4;
		wxPanel* m_panel9;
		wxPanel* m_panel10;
		wxPanel* RecvPage;
		wxNotebook* recvBook;
		wxPanel* FmtChange;
		wxNotebook* m_notebook4;
		wxPanel* m_panel6;
		wxPanel* m_panel7;
		wxStaticText* m_staticText3;
		wxButton* m_button8;

		// Virtual event handlers, override them in your derived class
		virtual void WndClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void refreshNetCard( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenNetCard( wxCommandEvent& event ) { event.Skip(); }
		virtual void SendEthnetFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void OpenSvPcap2Bin( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NetTools"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1298,692 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWnd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class recvPanel
///////////////////////////////////////////////////////////////////////////////
class recvPanel : public wxPanel
{
	private:

	protected:
		wxButton* BtStart;
		wxButton* m_button3;
		wxCheckBox* dispRtFrame;
		wxStaticText* recvCntText;
		wxButton* m_button5;
		wxButton* m_button6;
		wxButton* m_button4;
		wxChoice* SelItem1;
		wxChoice* SelCdt1;
		wxTextCtrl* SelText1;
		wxChoice* SelItem2;
		wxChoice* SelCdt2;
		wxTextCtrl* SelText2;
		wxSplitterWindow* m_splitter1;
		wxPanel* m_panel6;
		wxListCtrl* FrameList;
		wxPanel* m_panel7;
		wxTextCtrl* RtFrameText;
		wxTreeCtrl* RtFrameTree;
		wxTimer m_timer1;

		// Virtual event handlers, override them in your derived class
		virtual void BtStartPcap( wxCommandEvent& event ) { event.Skip(); }
		virtual void ClearFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void LoadXml( wxCommandEvent& event ) { event.Skip(); }
		virtual void LoadPcap( wxCommandEvent& event ) { event.Skip(); }
		virtual void SaveFile( wxCommandEvent& event ) { event.Skip(); }
		virtual void SelectFilterItem1( wxCommandEvent& event ) { event.Skip(); }
		virtual void SelectFilterCdt1( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetFilterCtx1( wxCommandEvent& event ) { event.Skip(); }
		virtual void SelectFilterItem2( wxCommandEvent& event ) { event.Skip(); }
		virtual void SelectFilterCdt2( wxCommandEvent& event ) { event.Skip(); }
		virtual void SetFilterCtx2( wxCommandEvent& event ) { event.Skip(); }
		virtual void FrameSelected( wxListEvent& event ) { event.Skip(); }
		virtual void SelNodeChange( wxTreeEvent& event ) { event.Skip(); }
		virtual void OnTimer( wxTimerEvent& event ) { event.Skip(); }


	public:

		recvPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1463,681 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~recvPanel();

		void m_splitter1OnIdle( wxIdleEvent& )
		{
			m_splitter1->SetSashPosition( 0 );
			m_splitter1->Disconnect( wxEVT_IDLE, wxIdleEventHandler( recvPanel::m_splitter1OnIdle ), NULL, this );
		}

};

