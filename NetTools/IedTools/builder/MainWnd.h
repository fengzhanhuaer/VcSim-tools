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
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/statbox.h>
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
/// Class TextPage
///////////////////////////////////////////////////////////////////////////////
class TextPage : public wxPanel
{
	private:

	protected:
		wxToolBar* m_toolBar2;
		wxChoice* UpdateMode;
		wxStaticText* PeriodMs;
		wxSpinCtrl* Period;
		wxStaticText* UpdatePara;
		wxSpinCtrl* m_spinCtrl3;
		wxButton* ManualUpdate;
		wxButton* ManualSet;
		wxRichTextCtrl* m_richText1;

	public:

		TextPage( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 692,538 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~TextPage();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CascadePage
///////////////////////////////////////////////////////////////////////////////
class CascadePage : public wxPanel
{
	private:

	protected:
		wxNotebook* m_notebook2;

	public:

		CascadePage( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~CascadePage();

};

///////////////////////////////////////////////////////////////////////////////
/// Class GridPage
///////////////////////////////////////////////////////////////////////////////
class GridPage : public wxPanel
{
	private:

	protected:
		wxToolBar* m_toolBar2;
		wxChoice* UpdateMode;
		wxStaticText* PeriodMs;
		wxSpinCtrl* Period;
		wxStaticText* UpdatePara;
		wxSpinCtrl* m_spinCtrl3;
		wxButton* ManualUpdate;
		wxButton* ManualSet;
		wxGrid* m_grid1;

	public:

		GridPage( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 968,532 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~GridPage();

};

///////////////////////////////////////////////////////////////////////////////
/// Class SetPage
///////////////////////////////////////////////////////////////////////////////
class SetPage : public wxPanel
{
	private:

	protected:
		wxToolBar* m_toolBar2;
		wxChoice* UpdateMode;
		wxStaticText* PeriodMs;
		wxSpinCtrl* Period;
		wxStaticText* UpdatePara;
		wxSpinCtrl* m_spinCtrl3;
		wxButton* ManualUpdate;
		wxButton* ManualSet;

	public:

		SetPage( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 762,525 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~SetPage();

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

		LogWnd( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("登录"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 463,254 ), long style = wxDEFAULT_DIALOG_STYLE );

		~LogWnd();

};

