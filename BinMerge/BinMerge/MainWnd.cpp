///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* Boot0;
	Boot0 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Boot0") ), wxHORIZONTAL );

	m_button4 = new wxButton( Boot0->GetStaticBox(), wxID_ANY, wxT("Boot0"), wxDefaultPosition, wxDefaultSize, 0 );
	Boot0->Add( m_button4, 0, wxALL, 5 );

	m_textCtrl1 = new wxTextCtrl( Boot0->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	Boot0->Add( m_textCtrl1, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( Boot0, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Uboot") ), wxHORIZONTAL );

	m_button2 = new wxButton( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Uboot"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer2->Add( m_button2, 0, wxALL, 5 );

	m_textCtrl2 = new wxTextCtrl( sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer2->Add( m_textCtrl2, 1, wxALL, 5 );


	bSizer2->Add( sbSizer2, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Sylix") ), wxHORIZONTAL );

	m_button5 = new wxButton( sbSizer4->GetStaticBox(), wxID_ANY, wxT("Sylix"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_button5, 0, wxALL, 5 );

	m_textCtrl3 = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer4->Add( m_textCtrl3, 1, wxALL, 5 );


	bSizer2->Add( sbSizer4, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("合成") ), wxVERTICAL );

	m_button6 = new wxButton( sbSizer7->GetStaticBox(), wxID_ANY, wxT("合成"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_button6, 1, wxALL|wxEXPAND, 5 );


	bSizer2->Add( sbSizer7, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddBoot0 ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddUboot ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddSylix ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::CreateBin ), NULL, this );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddBoot0 ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddUboot ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::AddSylix ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::CreateBin ), NULL, this );

}
