///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "FpgaUpdate.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxGridBagSizer* gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("第一步网卡选择："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	gbSizer1->Add( m_staticText41, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("第二步类型选择："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	gbSizer1->Add( m_staticText1, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_button1 = new wxButton( this, wxID_ANY, wxT("自动检测"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button1, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	gbSizer1->Add( m_textCtrl1, wxGBPosition( 1, 2 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );

	wxString m_choice1Choices[] = { wxT("NSA-FPGA-N1"), wxT("NSA-FPGA-N2") };
	int m_choice1NChoices = sizeof( m_choice1Choices ) / sizeof( wxString );
	m_choice1 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1NChoices, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	gbSizer1->Add( m_choice1, wxGBPosition( 1, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("第三步程序选择："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	gbSizer1->Add( m_staticText3, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	gbSizer1->Add( m_textCtrl3, wxGBPosition( 2, 2 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );

	m_button2 = new wxButton( this, wxID_ANY, wxT("打开"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button2, wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("第四步开始升级："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	gbSizer1->Add( m_staticText4, wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	wxArrayString m_choice2Choices;
	m_choice2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	gbSizer1->Add( m_choice2, wxGBPosition( 0, 1 ), wxGBSpan( 1, 2 ), wxALL|wxEXPAND, 5 );

	m_button4 = new wxButton( this, wxID_ANY, wxT("刷新网口"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button4, wxGBPosition( 0, 3 ), wxGBSpan( 1, 1 ), wxALL, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("开始"), wxDefaultPosition, wxDefaultSize, 0 );
	gbSizer1->Add( m_button3, wxGBPosition( 3, 1 ), wxGBSpan( 1, 3 ), wxALL|wxEXPAND, 5 );

	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	gbSizer1->Add( m_textCtrl4, wxGBPosition( 4, 0 ), wxGBSpan( 17, 5 ), wxALL|wxEXPAND, 5 );


	this->SetSizer( gbSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::CheckType ), NULL, this );
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::TypeChange ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenProgram ), NULL, this );
	m_choice2->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::NetCardChange ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ReFreshNetCard ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::StartUpdate ), NULL, this );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::CheckType ), NULL, this );
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::TypeChange ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::OpenProgram ), NULL, this );
	m_choice2->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::NetCardChange ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::ReFreshNetCard ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::StartUpdate ), NULL, this );

}
