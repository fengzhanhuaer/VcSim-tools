///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ConsoleWnd.h"

///////////////////////////////////////////////////////////////////////////

ConsoleWnd::ConsoleWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	NsaSeries = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	m_notebook4 = new wxNotebook( NsaSeries, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel3 = new wxPanel( m_notebook4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, 2, 0, 0 );

	m_button1 = new wxButton( m_panel3, wxID_ANY, wxT("FPGA升级"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer1->Add( m_button1, 0, wxALL, 5 );


	m_panel3->SetSizer( gSizer1 );
	m_panel3->Layout();
	gSizer1->Fit( m_panel3 );
	m_notebook4->AddPage( m_panel3, wxT("维护工具"), false );

	bSizer2->Add( m_notebook4, 1, wxEXPAND | wxALL, 5 );


	NsaSeries->SetSizer( bSizer2 );
	NsaSeries->Layout();
	bSizer2->Fit( NsaSeries );
	m_notebook2->AddPage( NsaSeries, wxT("NSA系列"), true );
	NgsSeries = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_notebook41 = new wxNotebook( NgsSeries, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel31 = new wxPanel( m_notebook41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer11;
	gSizer11 = new wxGridSizer( 0, 2, 0, 0 );

	m_button2 = new wxButton( m_panel31, wxID_ANY, wxT("虚拟液晶"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer11->Add( m_button2, 0, wxALL, 5 );


	m_panel31->SetSizer( gSizer11 );
	m_panel31->Layout();
	gSizer11->Fit( m_panel31 );
	m_notebook41->AddPage( m_panel31, wxT("维护工具"), false );
	m_panel6 = new wxPanel( m_notebook41, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer111;
	gSizer111 = new wxGridSizer( 0, 2, 0, 0 );

	m_button21 = new wxButton( m_panel6, wxID_ANY, wxT("ARM程序版本维护"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer111->Add( m_button21, 0, wxALL, 5 );


	m_panel6->SetSizer( gSizer111 );
	m_panel6->Layout();
	gSizer111->Fit( m_panel6 );
	m_notebook41->AddPage( m_panel6, wxT("开发工具"), true );

	bSizer3->Add( m_notebook41, 1, wxEXPAND | wxALL, 5 );


	NgsSeries->SetSizer( bSizer3 );
	NgsSeries->Layout();
	bSizer3->Fit( NgsSeries );
	m_notebook2->AddPage( NgsSeries, wxT("NGS系列"), false );
	GnrTools = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );

	m_notebook411 = new wxNotebook( GnrTools, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel311 = new wxPanel( m_notebook411, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer112;
	gSizer112 = new wxGridSizer( 0, 2, 0, 0 );

	m_button22 = new wxButton( m_panel311, wxID_ANY, wxT("网络监视"), wxDefaultPosition, wxDefaultSize, 0 );
	gSizer112->Add( m_button22, 0, wxALL, 5 );


	m_panel311->SetSizer( gSizer112 );
	m_panel311->Layout();
	gSizer112->Fit( m_panel311 );
	m_notebook411->AddPage( m_panel311, wxT("网络工具"), true );
	m_panel19 = new wxPanel( m_notebook411, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer1121;
	gSizer1121 = new wxGridSizer( 0, 2, 0, 0 );


	m_panel19->SetSizer( gSizer1121 );
	m_panel19->Layout();
	gSizer1121->Fit( m_panel19 );
	m_notebook411->AddPage( m_panel19, wxT("格式转换"), false );

	bSizer31->Add( m_notebook411, 1, wxEXPAND | wxALL, 5 );


	GnrTools->SetSizer( bSizer31 );
	GnrTools->Layout();
	bSizer31->Fit( GnrTools );
	m_notebook2->AddPage( GnrTools, wxT("公共工具"), false );

	bSizer1->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNsaFpgaUpdate ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNgsSimLcd ), NULL, this );
	m_button21->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNgsVerAdd ), NULL, this );
	m_button22->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenGnrNetCapture ), NULL, this );
}

ConsoleWnd::~ConsoleWnd()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNsaFpgaUpdate ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNgsSimLcd ), NULL, this );
	m_button21->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenNgsVerAdd ), NULL, this );
	m_button22->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ConsoleWnd::OpenGnrNetCapture ), NULL, this );

}
