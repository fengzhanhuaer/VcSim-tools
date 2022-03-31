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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/timer.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/dataview.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainWnd
///////////////////////////////////////////////////////////////////////////////
class MainWnd : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu2;
		wxToolBar* m_toolBar1;
		wxTextCtrl* ServerIp;
		wxButton* m_button1;
		wxBoxSizer* RootBox;
		wxTimer WndUpdate;
		wxTimer StatusTimer;
		wxStatusBar* m_statusBar1;

		// Virtual event handlers, override them in your derived class
		virtual void OnWndIdle( wxIdleEvent& event ) { event.Skip(); }
		virtual void ShowAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void LinkServer( wxCommandEvent& event ) { event.Skip(); }
		virtual void StatusUpdate( wxTimerEvent& event ) { event.Skip(); }


	public:

		MainWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("IedTools"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1151,683 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWnd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class TextWnd
///////////////////////////////////////////////////////////////////////////////
class TextWnd : public wxPanel
{
	private:

	protected:
		wxSpinCtrlDouble* dPara1;
		wxSpinCtrlDouble* dPara2;
		wxSpinCtrlDouble* dPara3;
		wxCheckBox* Check1;
		wxCheckBox* Check2;
		wxCheckBox* Check3;
		wxButton* Button1;
		wxButton* Button2;
		wxButton* Button3;
		wxChoice* updateMode;
		wxButton* UpdateButton;
		wxRichTextCtrl* text;

	public:

		TextWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1100,673 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~TextWnd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class GridWnd
///////////////////////////////////////////////////////////////////////////////
class GridWnd : public wxPanel
{
	private:

	protected:
		wxGrid* m_grid;

	public:

		GridWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~GridWnd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MyPanel10
///////////////////////////////////////////////////////////////////////////////
class MyPanel10 : public wxPanel
{
	private:

	protected:
		wxDataViewListCtrl* m_dataViewListCtrl000;

	public:

		MyPanel10( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~MyPanel10();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CascadeWnd
///////////////////////////////////////////////////////////////////////////////
class CascadeWnd : public wxPanel
{
	private:

	protected:
		wxListbook* ListPage;
		wxPanel* m_panel000;

	public:

		CascadeWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 834,595 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~CascadeWnd();

};

///////////////////////////////////////////////////////////////////////////////
/// Class LogWnd
///////////////////////////////////////////////////////////////////////////////
class LogWnd : public wxDialog
{
	private:

	protected:
		wxBoxSizer* LogBox;
		wxTextCtrl* idtext;
		wxTextCtrl* nametext;
		wxTextCtrl* pwtext;
		wxButton* m_button9;
		wxButton* m_button10;

		// Virtual event handlers, override them in your derived class
		virtual void Enter( wxCommandEvent& event ) { event.Skip(); }
		virtual void Cancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		LogWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("µÇÂ¼"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 463,254 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LogWnd();

};

