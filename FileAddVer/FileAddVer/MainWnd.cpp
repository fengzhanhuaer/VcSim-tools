///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWnd.h"

///////////////////////////////////////////////////////////////////////////

MainWnd::MainWnd( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	Path = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer2->Add( Path, 1, wxTOP|wxRIGHT|wxLEFT, 5 );

	Select = new wxButton( this, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( Select, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	wxString GngTypeChoices[] = { wxT("新一代") };
	int GngTypeNChoices = sizeof( GngTypeChoices ) / sizeof( wxString );
	GngType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, GngTypeNChoices, GngTypeChoices, 0 );
	GngType->SetSelection( 0 );
	bSizer3->Add( GngType, 0, wxALL, 5 );

	wxString ProgramTypeChoices[] = { wxT("自定义"), wxT("Sylix.T3BSP.Gzk"), wxT("Sylix.Boot0"), wxT("Sylix.UBoot") };
	int ProgramTypeNChoices = sizeof( ProgramTypeChoices ) / sizeof( wxString );
	ProgramType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, ProgramTypeNChoices, ProgramTypeChoices, 0 );
	ProgramType->SetSelection( 1 );
	bSizer3->Add( ProgramType, 0, wxALL, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	ProgramName = new wxTextCtrl( this, wxID_ANY, wxT("Sylix.T3BSP.Gzk"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( ProgramName, 1, wxALL|wxEXPAND, 5 );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Size"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer4->Add( m_staticText3, 0, wxALL, 5 );

	sizeM = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 2000, 5 );
	bSizer4->Add( sizeM, 0, wxALL, 5 );

	sizeK = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1024, 0 );
	bSizer4->Add( sizeK, 0, wxALL, 5 );

	sizeB = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1024, 0 );
	bSizer4->Add( sizeB, 0, wxALL, 5 );


	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	Prger = new wxTextCtrl( this, wxID_ANY, wxT("fengzhanhua"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( Prger, 1, wxALL, 5 );

	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("V"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	Vmajor = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 1 );
	bSizer5->Add( Vmajor, 0, wxALL, 5 );

	Vminor = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 10 );
	bSizer5->Add( Vminor, 0, wxALL, 5 );

	Vdel = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 0 );
	bSizer5->Add( Vdel, 0, wxTOP|wxBOTTOM|wxLEFT, 5 );


	bSizer1->Add( bSizer5, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_datePicker1 = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
	bSizer6->Add( m_datePicker1, 0, wxALL, 5 );

	m_timePicker1 = new wxTimePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxTP_DEFAULT );
	bSizer6->Add( m_timePicker1, 0, wxALL, 5 );

	Crc = new wxStaticText( this, wxID_ANY, wxT("Crc"), wxDefaultPosition, wxDefaultSize, 0 );
	Crc->Wrap( -1 );
	bSizer6->Add( Crc, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	tCrc = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	bSizer6->Add( tCrc, 0, wxALL, 5 );


	bSizer1->Add( bSizer6, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_button2 = new wxButton( this, wxID_ANY, wxT("读取"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button2, 1, wxALL|wxEXPAND, 5 );

	m_button3 = new wxButton( this, wxID_ANY, wxT("生成"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button3, 1, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer7, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	Select->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SelectFile ), NULL, this );
	ProgramType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::TypeChange ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::readfromfile ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::creatfile ), NULL, this );
}

MainWnd::~MainWnd()
{
	// Disconnect Events
	Select->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::SelectFile ), NULL, this );
	ProgramType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainWnd::TypeChange ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::readfromfile ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWnd::creatfile ), NULL, this );

}
